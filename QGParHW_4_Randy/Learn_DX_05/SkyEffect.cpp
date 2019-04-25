#include "Effects.h"
#include "d3dUtil.h"
#include "EffectHelper.h"	// ��������Effects.h��d3dUtil.h����
#include "DXTrace.h"
#include "Vertex.h"
using namespace DirectX;
using namespace std::experimental;


//
// SkyEffect::Impl ��Ҫ����SkyEffect�Ķ���
//

class SkyEffect::Impl : public AlignedType<SkyEffect::Impl>
{
public:
	//
	// ��Щ�ṹ���ӦHLSL�Ľṹ�塣��Ҫ��16�ֽڶ���
	//

	struct CBChangesEveryFrame
	{
		DirectX::XMMATRIX worldViewProj;
	};

public:
	// ������ʽָ��
	Impl() = default;
	~Impl() = default;

public:
	CBufferObject<0, CBChangesEveryFrame>	m_CBFrame;	// ÿ֡���Ƶĳ���������

	BOOL m_IsDirty;										// �Ƿ���ֵ���
	std::vector<CBufferBase*> m_pCBuffers;				// ͳһ�����������еĳ���������

	ComPtr<ID3D11VertexShader> m_pSkyVS;
	ComPtr<ID3D11PixelShader> m_pSkyPS;

	ComPtr<ID3D11InputLayout> m_pVertexPosLayout;

	ComPtr<ID3D11ShaderResourceView> m_pTextureCube;			// ��պ�����
};

//
// SkyEffect
//

namespace
{
	// SkyEffect����
	static SkyEffect * g_pInstance = nullptr;
}

SkyEffect::SkyEffect()
{
	if (g_pInstance)
		throw std::exception("SkyEffect is a singleton!");
	g_pInstance = this;
	pImpl = std::make_unique<SkyEffect::Impl>();
}

SkyEffect::~SkyEffect()
{
}

SkyEffect::SkyEffect(SkyEffect && moveFrom)
{
	pImpl.swap(moveFrom.pImpl);
}

SkyEffect & SkyEffect::operator=(SkyEffect && moveFrom)
{
	pImpl.swap(moveFrom.pImpl);
	return *this;
}

SkyEffect & SkyEffect::Get()
{
	if (!g_pInstance)
		throw std::exception("SkyEffect needs an instance!");
	return *g_pInstance;
}

bool SkyEffect::InitAll(ComPtr<ID3D11Device> device)
{
	if (!device)
		return false;

	if (!pImpl->m_pCBuffers.empty())
		return true;

	if (!RenderStates::IsInit())
		throw std::exception("RenderStates need to be initialized first!");

	ComPtr<ID3DBlob> blob2;
	
	// ******************
	// ����������ɫ��
	//

	HR(CreateShaderFromFile(L"HLSL\\Sky_VS.cso", L"HLSL\\Sky_VS.hlsl", "VS", "vs_5_0", blob2.ReleaseAndGetAddressOf()));
	HR(device->CreateVertexShader(blob2->GetBufferPointer(), blob2->GetBufferSize(), nullptr, pImpl->m_pSkyVS.GetAddressOf()));
	// �������㲼��
	HR(device->CreateInputLayout(VertexPos::inputLayout, ARRAYSIZE(VertexPos::inputLayout),
		blob2->GetBufferPointer(), blob2->GetBufferSize(), pImpl->m_pVertexPosLayout.GetAddressOf()));

	// ******************
	// ����������ɫ��
	//

	HR(CreateShaderFromFile(L"HLSL\\Sky_PS.cso", L"HLSL\\Sky_PS.hlsl", "PS", "ps_5_0", blob2.ReleaseAndGetAddressOf()));
	HR(device->CreatePixelShader(blob2->GetBufferPointer(), blob2->GetBufferSize(), nullptr, pImpl->m_pSkyPS.GetAddressOf()));


	pImpl->m_pCBuffers.assign({
		&pImpl->m_CBFrame,
	});

	// ��������������
	for (auto& pBuffer : pImpl->m_pCBuffers)
	{
		HR(pBuffer->CreateBuffer(device));
	}

	return true;
}

void SkyEffect::SetRenderDefault(ComPtr<ID3D11DeviceContext> deviceContext)
{
	deviceContext->IASetInputLayout(pImpl->m_pVertexPosLayout.Get());
	deviceContext->VSSetShader(pImpl->m_pSkyVS.Get(), nullptr, 0);
	deviceContext->PSSetShader(pImpl->m_pSkyPS.Get(), nullptr, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->GSSetShader(nullptr, nullptr, 0);
	deviceContext->RSSetState(RenderStates::RSNoCull.Get());

	deviceContext->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());
	deviceContext->OMSetDepthStencilState(RenderStates::DSSLessEqual.Get(), 0);
	deviceContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
}

void XM_CALLCONV SkyEffect::SetWorldViewProjMatrix(DirectX::FXMMATRIX W, DirectX::CXMMATRIX V, DirectX::CXMMATRIX P)
{
	auto& cBuffer = pImpl->m_CBFrame;
	cBuffer.data.worldViewProj = XMMatrixTranspose(W * V * P);
	pImpl->m_IsDirty = cBuffer.isDirty = true;
}

void XM_CALLCONV SkyEffect::SetWorldViewProjMatrix(DirectX::FXMMATRIX WVP)
{
	auto& cBuffer = pImpl->m_CBFrame;
	cBuffer.data.worldViewProj = XMMatrixTranspose(WVP);
	pImpl->m_IsDirty = cBuffer.isDirty = true;
}

void SkyEffect::SetTextureCube(ComPtr<ID3D11ShaderResourceView> m_pTextureCube)
{
	pImpl->m_pTextureCube = m_pTextureCube;
}

void SkyEffect::Apply(ComPtr<ID3D11DeviceContext> deviceContext)
{
	auto& pCBuffers = pImpl->m_pCBuffers;
	// ���������󶨵���Ⱦ������
	pCBuffers[0]->BindVS(deviceContext);
	
	// ����SRV
	deviceContext->PSSetShaderResources(0, 1, pImpl->m_pTextureCube.GetAddressOf());

	if (pImpl->m_IsDirty)
	{
		pImpl->m_IsDirty = false;
		for (auto& pCBuffer : pCBuffers)
		{
			pCBuffer->UpdateBuffer(deviceContext);
		}
	}
}

