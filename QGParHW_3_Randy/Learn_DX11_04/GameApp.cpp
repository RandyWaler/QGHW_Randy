#include "GameApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
using namespace DirectX;
using namespace std::experimental;



GameApp::GameApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

GameApp::~GameApp()
{
}

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	if (!InitEffect())
		return false;

	if (!InitResource())
		return false;

	// ��ʼ����꣬���̲���Ҫ
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

	return true;
}

void GameApp::OnResize()
{


	assert(m_pd2dFactory);
	assert(m_pdwriteFactory);
	// �ͷ�D2D�������Դ
	m_pColorBrush.Reset();
	m_pd2dRenderTarget.Reset();

	D3DApp::OnResize();

	// ΪD2D����DXGI������ȾĿ��
	ComPtr<IDXGISurface> surface;
	HR(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(surface.GetAddressOf())));
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(surface.Get(), &props, m_pd2dRenderTarget.GetAddressOf());
	surface.Reset();

	if (hr == E_NOINTERFACE)
	{
		OutputDebugString(L"\n���棺Direct2D��Direct3D�������Թ������ޣ��㽫�޷������ı���Ϣ�����ṩ������ѡ������\n"
			"1. ����Win7ϵͳ����Ҫ������Win7 SP1������װKB2670838������֧��Direct2D��ʾ��\n"
			"2. �������Direct3D 10.1��Direct2D�Ľ�����������ģ�"
			"https://docs.microsoft.com/zh-cn/windows/desktop/Direct2D/direct2d-and-direct3d-interoperation-overview""\n"
			"3. ʹ�ñ������⣬����FreeType��\n\n");
	}
	else if (hr == S_OK)
	{
		// �����̶���ɫˢ���ı���ʽ
		HR(m_pd2dRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			m_pColorBrush.GetAddressOf()));
		HR(m_pdwriteFactory->CreateTextFormat(L"����", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"zh-cn",
			m_pTextFormat.GetAddressOf()));
	}
	else
	{
		// �����쳣����
		assert(m_pd2dRenderTarget);
	}

	
}

void GameApp::UpdateScene(float dt)
{
	static float roZ = 0.0f;
	// ��ȡ����״̬
	Keyboard::State keyState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keyState);
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::D1))
	{
		nowType = NowPlayType::Cube00;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
		auto meshData = Geometry::CreateBox();
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D.Get(), nullptr, 0);
	}
	else if (m_KeyboardTracker.IsKeyPressed(Keyboard::D2)) {
		nowType = NowPlayType::Anima;
		m_CurrFrame = 0;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout2D.Get());
		auto meshData = Geometry::Create2DShow();
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader2D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader2D.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pFireAnims[0].GetAddressOf());
		
	}
	else if (m_KeyboardTracker.IsKeyPressed(Keyboard::D3)) {

		
		

		nowType = NowPlayType::Cube01;
		m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D2.Get());
		auto meshData = Geometry::CreateBox();
		ResetMesh(meshData);
		m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D2.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D2.Get(), nullptr, 0);
		m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_proCubeTex.GetAddressOf());
		m_pd3dImmediateContext->PSSetShaderResources(1, 1, m_proCubeTex2.GetAddressOf());

		
	
	}
	if (nowType == NowPlayType::Cube00|| nowType == NowPlayType::Cube01) {
		static float rotateX = 0.0f, rotateY = 0.0f;

		static XMFLOAT3 movePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

		static float scal = 1.0f;

		// ��ȡ���״̬
		Mouse::State mouseState = m_pMouse->GetState();
		Mouse::State lastMouseState = m_MouseTracker.GetLastState();


		// ������갴ť״̬������
		m_MouseTracker.Update(mouseState);


		mouseMoveX = mouseState.x - lastMouseState.x;
		mouseMoveY = mouseState.y - lastMouseState.y;

		if (mouseState.leftButton == true && mouseState.leftButton == m_MouseTracker.HELD) {//�����סʱ��������ת
			rotateY -= mouseMoveX * 0.01f;
			rotateX -= mouseMoveY * 0.01f;

		}
		//��������û��ʹ��else if ����...���������ͬʱ��ס�������Ҽ�...
		if (mouseState.rightButton == true && mouseState.rightButton == m_MouseTracker.HELD) {//�Ҽ���סʱ�������ƶ�
			if (mouseMoveX > 0) {//�����ƶ�
				if (movePos.x + mouseMoveX * 0.01f <= moveRect) {
					movePos.x += mouseMoveX * 0.01f;
				}
			}
			else//�����ƶ�
			{
				if (movePos.x + mouseMoveX * 0.01f >= -moveRect) {
					movePos.x += mouseMoveX * 0.01f;
				}
			}
			if (mouseMoveY < 0) {//�����ƶ�
				if (movePos.y <= moveRect) {
					movePos.y -= mouseMoveY * 0.01f;
				}
			}
			else//�����ƶ�
			{
				if (movePos.y >= -moveRect) {
					movePos.y -= mouseMoveY * 0.01f;
				}
			}
		}
		//�����̰��� �Ŵ���С׵��
		if (keyState.IsKeyDown(Keyboard::Q)) {
			if (scal <= 2.0f) {
				scal += 0.001f;
			}
		}
		else if (keyState.IsKeyDown(Keyboard::E)) {
			if (scal >= 0.0f) {
				scal -= 0.001f;
			}
		}



		m_VSConstantBuffer.world = XMMatrixTranspose(XMMatrixScaling(scal, scal, scal)*((XMMatrixRotationY(rotateY))*XMMatrixRotationX(rotateX))*XMMatrixTranslation(movePos.x, movePos.y, 0.0f));
		m_VSConstantBuffer.worldInvTranspose = XMMatrixInverse(nullptr, XMMatrixRotationX(rotateX) * XMMatrixRotationY(rotateY));



		//// ���³�������������������ת����
		D3D11_MAPPED_SUBRESOURCE mappedData;
		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(VSConstantBuffer), &m_VSConstantBuffer, sizeof(VSConstantBuffer));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[0].Get(), 0);

		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_PSConstantBuffer, sizeof(PSConstantBuffer));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);

		if (nowType == NowPlayType::Cube01) {
			// ��ת��������������ӦHLSL�Ĵ���b2�ĳ���������
			m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBuffers[2].GetAddressOf());

			
			roZ += 0.001f;

			m_PSConstantBufferRotate.rotate = XMMatrixTranspose(XMMatrixTranslation(-0.5f,-0.5f,0)*XMMatrixRotationZ(roZ)*XMMatrixTranslation(0.5f,0.5f,0));
			HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
			memcpy_s(mappedData.pData, sizeof(PSConstantBufferRotate), &m_PSConstantBufferRotate, sizeof(PSConstantBufferRotate));
			m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);


		}

	}
	else if (nowType == NowPlayType::Anima) {
		// ����������1��60֡
		static float totDeltaTime = 0;

		totDeltaTime += dt;
		if (totDeltaTime > 1.0f / 60)
		{
			totDeltaTime -= 1.0f / 60;
			m_CurrFrame = (m_CurrFrame + 1) % 120;
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pFireAnims[m_CurrFrame].GetAddressOf());
		}
	}
}

void GameApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);

	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	if (nowType == NowPlayType::Cube00) {
		for (int i = 0; i < 6; i++) {
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pCubeTex[i].GetAddressOf());
			m_pd3dImmediateContext->DrawIndexed( 6, i*6, 0);
		}
	}
	else if (nowType == NowPlayType::Cube01) {
		m_pd3dImmediateContext->DrawIndexed(m_IndexCount, 0, 0);
	}
	else
	{
		
		m_pd3dImmediateContext->DrawIndexed(m_IndexCount, 0, 0);
	}

	//
	// ����Direct2D����
	//
	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->BeginDraw();
		static const WCHAR* textStr = L"1-����������&ƽ�й�(3D)\n2-���涯��(2D)\n3-������ת����&������&�޹���(3D)\n";
		m_pd2dRenderTarget->DrawTextW(textStr, (UINT32)wcslen(textStr), m_pTextFormat.Get(),
			D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, m_pColorBrush.Get());
		static const WCHAR* textStr2 = L"2019QG�������������4��С����ѵ\nRandy\n2019.04.18\\10��13��\n";
		m_pd2dRenderTarget->DrawTextW(textStr2, (UINT32)wcslen(textStr2), m_pTextFormat.Get(),
			D2D1_RECT_F{ 800.0f, 0.0f, 600.0f, 200.0f }, m_pColorBrush.Get());
		HR(m_pd2dRenderTarget->EndDraw());
	}


	HR(m_pSwapChain->Present(0, 0));
}


bool GameApp::InitEffect()
{
	ComPtr<ID3DBlob> blob;

	// ����������ɫ��(2D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS_2D.cso", L"HLSL\\Basic_VS_2D.hlsl", "VS_2D", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader2D.GetAddressOf()));
	// �������㲼��(2D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosTex::inputLayout, ARRAYSIZE(VertexPosTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout2D.GetAddressOf()));

	// ����������ɫ��(2D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_PS_2D.cso", L"HLSL\\Basic_PS_2D.hlsl", "PS_2D", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader2D.GetAddressOf()));

	// ����������ɫ��(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_VS_3D.cso", L"HLSL\\Basic_VS_3D.hlsl", "VS_3D", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader3D.GetAddressOf()));

	// �������㲼��(3D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout3D.GetAddressOf()));



	// ����������ɫ��(3D)
	HR(CreateShaderFromFile(L"HLSL\\Basic_PS_3D.cso", L"HLSL\\Basic_PS_3D.hlsl", "PS_3D", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader3D.GetAddressOf()));

	// ����������ɫ��(3D) ---�޹���
	HR(CreateShaderFromFile(L"HLSL\\Cube_VS.cso", L"HLSL\\Cube_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader3D2.GetAddressOf()));

	// �������㲼��(3D)
	HR(m_pd3dDevice->CreateInputLayout(VertexPosNormalTex::inputLayout, ARRAYSIZE(VertexPosNormalTex::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout3D2.GetAddressOf()));

	// ����������ɫ��(3D) ---�޹���
	HR(CreateShaderFromFile(L"HLSL\\Cube_PS.cso", L"HLSL\\Cube_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader3D2.GetAddressOf()));

	return true;
}

bool GameApp::InitResource()
{
// ��ʼ������ģ��
	auto meshData = Geometry::CreateBox();
	ResetMesh(meshData);


	// ******************
	// ���ó�������������
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(VSConstantBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �½�����VS��PS�ĳ���������
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[0].GetAddressOf()));


	cbd.ByteWidth = sizeof(PSConstantBuffer);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[1].GetAddressOf()));

	cbd.ByteWidth = sizeof(PSConstantBufferRotate);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[2].GetAddressOf()));

	// ��������
	//��������������
	WCHAR strCube[40];
	for (int i = 0; i < 6; i++) {
		wsprintf(strCube, L"Texture\\Cube%02d.jpg", i);
		HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), strCube, nullptr, m_pCubeTex[i].GetAddressOf()));
	}

	// ��ʼ����������
	WCHAR strFile[40];
	m_pFireAnims.resize(120);
	for (int i = 1; i <= 120; ++i)
	{
		wsprintf(strFile, L"Texture\\FireAnim\\Fire%03d.bmp", i);
		HR(CreateWICTextureFromFile(m_pd3dDevice.Get(), strFile, nullptr, m_pFireAnims[i - 1].GetAddressOf()));
	}
	//������ת����ʹ��
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\flare.dds", nullptr, m_proCubeTex.GetAddressOf()));
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\flarealpha.dds", nullptr, m_proCubeTex2.GetAddressOf()));

	// ��ʼ����������Դ
	//ComPtr<ID3D11Texture2D> test;

	//HR(CreateDDSTexture2DArrayFromFile(
	//	m_pd3dDevice.Get(),
	//	m_pd3dImmediateContext.Get(),
	//	std::vector<std::wstring>{
	//	L"Texture\\flare.dds"},
	//	test.GetAddressOf(),
	//		m_proCubeTex.GetAddressOf()));
	//HR(CreateDDSTexture2DArrayFromFile(
	//	m_pd3dDevice.Get(),
	//	m_pd3dImmediateContext.Get(),
	//	std::vector<std::wstring>{
	//	L"Texture\\flarealpha.dds"},
	//	test.GetAddressOf(),
	//		m_proCubeTex2.GetAddressOf()));

	// ��ʼ��������״̬
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));


	// ��ʼ��Ĭ�Ϲ���
	// �����
	m_DirLight.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_DirLight.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_DirLight.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_DirLight.Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
	
	// ��ʼ������VS�ĳ�����������ֵ
	m_VSConstantBuffer.world = XMMatrixIdentity();
	m_VSConstantBuffer.view = XMMatrixTranspose(XMMatrixLookAtLH(
		XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	));
	m_VSConstantBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));
	m_VSConstantBuffer.worldInvTranspose = XMMatrixIdentity();



	// ��ʼ������PS�ĳ�����������ֵ
	m_PSConstantBuffer.material.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PSConstantBuffer.material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_PSConstantBuffer.material.Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	// ʹ��Ĭ��ƽ�й�
	m_PSConstantBuffer.dirLight = m_DirLight;
	// ע�ⲻҪ�������ô˴��Ĺ۲�λ�ã�����������ֻ�������
	m_PSConstantBuffer.eyePos = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);

	// ����PS������������Դ
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(PSConstantBuffer), &m_VSConstantBuffer, sizeof(PSConstantBuffer));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);


	m_PSConstantBufferRotate.rotate= XMMatrixIdentity();

	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(PSConstantBufferRotate), &m_PSConstantBufferRotate, sizeof(PSConstantBufferRotate));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);


	// ******************
	// ����Ⱦ���߸����׶ΰ󶨺�������Դ

	// ����ͼԪ���ͣ��趨���벼��
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
	// ����ɫ���󶨵���Ⱦ����
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D.Get(), nullptr, 0);
	// VS������������ӦHLSL�Ĵ���b0�ĳ���������
	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
	// PS������������ӦHLSL�Ĵ���b1�ĳ���������
	m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	// ��ת��������������ӦHLSL�Ĵ���b2�ĳ���������
	m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pConstantBuffers[2].GetAddressOf());

	// ������ɫ�׶����úò�����
	m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D.Get(), nullptr, 0);
	


	nowType = Cube00;


	return true;
}
template<class VertexType>
bool GameApp::ResetMesh(const Geometry::MeshData<VertexType>& meshData)
{
	// �ͷž���Դ
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();



	// ���ö��㻺��������
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)meshData.vertexVec.size() * sizeof(VertexType);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// �½����㻺����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = meshData.vertexVec.data();
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

	// ����װ��׶εĶ��㻺��������
	UINT stride = sizeof(VertexType);			// ��Խ�ֽ���
	UINT offset = 0;							// ��ʼƫ����

	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);



	// ������������������
	m_IndexCount = (UINT)meshData.indexVec.size();
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(WORD) * m_IndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	// �½�����������
	InitData.pSysMem = meshData.indexVec.data();
	HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
	// ����װ��׶ε���������������
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	return true;
}
