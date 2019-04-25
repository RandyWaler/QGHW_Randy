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

	// ����ȳ�ʼ��������Ⱦ״̬���Թ��������Чʹ��
	RenderStates::InitAll(m_pd3dDevice);
	if (!m_SkyEffect.InitAll(m_pd3dDevice))
		return false;

	if (!InitResource())
		return false;

	// ��ʼ����꣬���̲���Ҫ
	m_pMouse->SetWindow(m_hMainWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_RELATIVE);

	pickingSphere = nullptr;

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
			DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"zh-cn",
			m_pTextFormat.GetAddressOf()));
	}
	else
	{
		// �����쳣����
		assert(m_pd2dRenderTarget);
	}
	
	// ����������ʾ
	if (m_pCamera != nullptr)
	{
		m_pCamera->SetFrustum(XM_PI / 3, AspectRatio(), 0.5f, 1000.0f);
		m_pCamera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
		m_CBOnResize.proj = XMMatrixTranspose(m_pCamera->GetProjXM());
		
		D3D11_MAPPED_SUBRESOURCE mappedData;
		HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
		memcpy_s(mappedData.pData, sizeof(CBChangesOnResize), &m_CBOnResize, sizeof(CBChangesOnResize));
		m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);
	}
}

void GameApp::UpdateScene(float dt)
{
	// ��������¼�����ȡ���ƫ����
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	m_MouseTracker.Update(mouseState);
	// ���¼����¼�
	Keyboard::State keyState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keyState);
//Camera Move----------------------------------------------------------------------------------------------------------
	// ��ȡ����
	auto cam1st = std::dynamic_pointer_cast<FirstPersonCamera>(m_pCamera);


		// ��һ�˳�/����������Ĳ���

		// �����ƶ�
		if (keyState.IsKeyDown(Keyboard::W))
		    cam1st->MoveForward(dt * 3.0f);	
		if (keyState.IsKeyDown(Keyboard::S))
			cam1st->MoveForward(dt * -3.0f);
		if (keyState.IsKeyDown(Keyboard::A))
			cam1st->Strafe(dt * -3.0f);
		if (keyState.IsKeyDown(Keyboard::D))
			cam1st->Strafe(dt * 3.0f);
		if (keyState.IsKeyDown(Keyboard::Q))
			cam1st->MoveVertical(dt*-3.0f);
		if (keyState.IsKeyDown(Keyboard::E))
			cam1st->MoveVertical(dt*3.0f);

		// ��λ��������[-8.9f, 8.9f]��������
		// ��Ұ��ת����ֹ��ʼ�Ĳ�ֵ�����µ�ͻȻ��ת
		cam1st->Pitch(mouseState.y * dt * 1.25f);
		cam1st->RotateY(mouseState.x * dt * 1.25f);
	


	// ���¹۲����
	m_pCamera->UpdateViewMatrix();
	XMStoreFloat4(&m_CBFrame.eyePos, m_pCamera->GetPositionXM());
	m_CBFrame.view = XMMatrixTranspose(m_pCamera->GetViewXM());	

//Picking----------------------------------------------------------------------------------------------------------
	if (mouseState.leftButton == true) { //����һ�ε����������֡Ϊtrue
		if (!pickingSphere) {
			Ray ray = Ray::ScreenToRay(*m_pCamera, 400.0f, 300.0f);
			
			for (int i = 0; i < 6; i++) {
				if (m_Sphere[i].IsVisible()&&ray.Hit(m_Sphere[i].GetBounding())) {
					m_PickedObjStr = L"\n�ɿ���������������";
					m_Sphere[i].endMove();
					pickingSphere = &m_Sphere[i];
					break;
				}
			}
		}

	}
	else {//���ﲻ������״̬���ͷ�
		m_PickedObjStr = L"\n�����������ס��������ʰȡ����";
		if(pickingSphere){
			if (pickingSphere->IsVisible()) {//����ʰȡ������������Բ��������Ͳ���������
				pickingSphere->StartMove(m_pCamera->GetLookXM());
			}
			pickingSphere = nullptr;
		}
	}

	if (pickingSphere&&pickingSphere->IsVisible()) {
		XMFLOAT3 pos= m_pCamera->GetPosition();
		pickingSphere->SetWorldMatrix(XMMatrixTranslation(pos.x, pos.y,pos.z)*XMMatrixTranslationFromVector(m_pCamera->GetLookXM()*3.0f));
	}

	for (int i = 0; i < 6; i++) {
		if (m_Sphere[i].IsVisible()) {
			m_Sphere[i].updateMove(dt);
			for (int j = 0; j < 6; j++) {
				if (m_Cylinder[j].IsVisible()&&m_Sphere[i].GetBounding().Contains(m_Cylinder[j].GetBounding())) {
					m_Sphere[i].endMove();
					m_Sphere[i].setIsVisible(false);
					m_Cylinder[j].setIsVisible(false);
				}
			}
		}
	}
	if (keyState.IsKeyDown(Keyboard::Space)) {//������������
		for (int i = 0; i < 6; i++) {
			m_Cylinder[i].reSet(-9 + i * 4, 0, 5 * pow(-1, i));
	
		}
		for (int i = 0; i < 6; i++) {
			m_Sphere[i].reSet(-9 + i * 4, 0, 3 * pow(-1, i - 1));
			
		}
		pickingSphere = nullptr;
	}

	// �˳���������Ӧ�򴰿ڷ���������Ϣ
	if (keyState.IsKeyDown(Keyboard::Escape))
		SendMessage(MainWnd(), WM_DESTROY, 0, 0);
	
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(CBChangesEveryFrame), &m_CBFrame, sizeof(CBChangesEveryFrame));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[1].Get(), 0);
}

void GameApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);

	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), reinterpret_cast<const float*>(&Colors::Black));
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//
	// ���Ƽ���ģ��
	//

	reSetGameObjEffect();

	m_Floor.Draw(m_pd3dImmediateContext);

	for (int i = 0; i < 6; i++) {
		m_Cylinder[i].Draw(m_pd3dImmediateContext);
	}
	for (int i = 0; i < 6; i++) {
		m_Sphere[i].Draw(m_pd3dImmediateContext);
	}

	//
	//������պ�
	//
	m_SkyEffect.SetRenderDefault(m_pd3dImmediateContext);
	m_pSunset->Draw(m_pd3dImmediateContext, m_SkyEffect, *m_pCamera);



	//
	//
	// ����Direct2D����
	//
	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->BeginDraw();
		std::wstring text;
			text += L"�����ӽ�\nWASD+QE�ƶ�";
			text += L"\n�ո����ó���";
			text += m_PickedObjStr;
		m_pd2dRenderTarget->DrawTextW(text.c_str(), (UINT32)text.length(), m_pTextFormat.Get(),
			D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, m_pColorBrush.Get());
		std::wstring text2=L"+";
		m_pd2dRenderTarget->DrawTextW(text2.c_str(), (UINT32)text2.length(), m_pTextFormat.Get(),
			D2D1_RECT_F{ 399.0f, 299.0f, 800.0f, 600.0f }, m_pColorBrush.Get());
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

	return true;
}

bool GameApp::InitResource()
{
	// ******************
	// ���ó�������������
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �½�����VS��PS�ĳ���������
	cbd.ByteWidth = sizeof(CBChangesEveryDrawing);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[0].GetAddressOf()));
	cbd.ByteWidth = sizeof(CBChangesEveryFrame);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[1].GetAddressOf()));
	cbd.ByteWidth = sizeof(CBChangesOnResize);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[2].GetAddressOf()));
	cbd.ByteWidth = sizeof(CBChangesRarely);
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffers[3].GetAddressOf()));
	// ******************
	// ��ʼ����Ϸ����
	ComPtr<ID3D11ShaderResourceView> texture;
	ComPtr<ID3D11ShaderResourceView> texture_s;
	ComPtr<ID3D11ShaderResourceView> texture_s2;
	// ��ʼ���ذ�
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\floor.dds", nullptr, texture.ReleaseAndGetAddressOf()));
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\stones.dds", nullptr, texture_s.ReleaseAndGetAddressOf()));
	HR(CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"Texture\\stone.dds", nullptr, texture_s2.ReleaseAndGetAddressOf()));
	m_Floor.SetBuffer(m_pd3dDevice, 
		Geometry::CreatePlane(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(25.0f, 25.0f), XMFLOAT2(5.0f, 5.0f)));
	m_Floor.SetTexture(texture);

	for (int i = 0; i < 6; i++) {
		m_Cylinder[i].creatCylinder(m_pd3dDevice, -9+i*4, 0, 5*pow(-1,i));
		m_Cylinder[i].SetTexture(texture_s);
	}
	for (int i = 0; i < 6; i++) {
		m_Sphere[i].creatSphere(m_pd3dDevice, -9 + i * 4, 0, 3 * pow(-1, i-1));
		m_Sphere[i].SetTexture(texture_s2);
	}

	// ******************
	// ��ʼ����պ����
	m_pSunset = std::make_unique<SkyRender>(
		m_pd3dDevice, m_pd3dImmediateContext,
		std::vector<std::wstring>{
		L"Texture\\PX.png", L"Texture\\NX.png",
			L"Texture\\PY.png", L"Texture\\NY.png",
			L"Texture\\PZ.png", L"Texture\\NZ.png", },
		5000.0f);
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

	
	// ******************
	// ��ʼ��������������ֵ
	// ��ʼ��ÿ֡���ܻ�仯��ֵ
	auto camera = std::shared_ptr<FirstPersonCamera>(new FirstPersonCamera);
	m_pCamera = camera;
	camera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
	camera->LookAt(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));

	// ��ʼ�����ڴ��ڴ�С�䶯ʱ�޸ĵ�ֵ
	m_pCamera->SetFrustum(XM_PI / 3, AspectRatio(), 0.5f, 1000.0f);
	m_CBOnResize.proj = XMMatrixTranspose(m_pCamera->GetProjXM());

	// ��ʼ������仯��ֵ
	// ������
	m_CBRarely.dirLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBRarely.dirLight[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_CBRarely.dirLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBRarely.dirLight[0].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	// �ƹ�
	m_CBRarely.pointLight[0].Position = XMFLOAT3(0.0f, 10.0f, 0.0f);
	m_CBRarely.pointLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBRarely.pointLight[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_CBRarely.pointLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBRarely.pointLight[0].Att = XMFLOAT3(0.0f, 0.1f, 0.0f);
	m_CBRarely.pointLight[0].Range = 25.0f;
	m_CBRarely.numDirLight = 1;
	m_CBRarely.numPointLight = 1;
	m_CBRarely.numSpotLight = 0;
	// ��ʼ������
	m_CBRarely.material.Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBRarely.material.Diffuse = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	m_CBRarely.material.Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 50.0f);


	// ���²����ױ��޸ĵĳ�����������Դ
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[2].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(CBChangesOnResize), &m_CBOnResize, sizeof(CBChangesOnResize));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[2].Get(), 0);

	HR(m_pd3dImmediateContext->Map(m_pConstantBuffers[3].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(CBChangesRarely), &m_CBRarely, sizeof(CBChangesRarely));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffers[3].Get(), 0);

	return true;
}

void GameApp::reSetGameObjEffect()
{
	// ����Ⱦ���߸����׶ΰ󶨺�������Դ
	// ����ͼԪ���ͣ��趨���벼��
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout3D.Get());
	// Ĭ�ϰ�3D��ɫ��
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader3D.Get(), nullptr, 0);
	// Ԥ�Ȱ󶨸�������Ļ�����������ÿ֡���µĻ�������Ҫ�󶨵�������������
	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffers[0].GetAddressOf());
	m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pConstantBuffers[2].GetAddressOf());

	m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBuffers[1].GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(3, 1, m_pConstantBuffers[3].GetAddressOf());
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader3D.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
}

GameApp::GameObject::GameObject()
	: m_WorldMatrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f)
{
}

DirectX::XMFLOAT3 GameApp::GameObject::GetPosition() const
{
	return XMFLOAT3(m_WorldMatrix(3, 0), m_WorldMatrix(3, 1), m_WorldMatrix(3, 2));
}

template<class VertexType, class IndexType>
void GameApp::GameObject::SetBuffer(ComPtr<ID3D11Device> device, const Geometry::MeshData<VertexType, IndexType>& meshData)
{
	// �ͷž���Դ
	m_pVertexBuffer.Reset();
	m_pIndexBuffer.Reset();

	// ���ö��㻺��������
	m_VertexStride = sizeof(VertexType);
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = (UINT)meshData.vertexVec.size() * m_VertexStride;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// �½����㻺����
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = meshData.vertexVec.data();
	HR(device->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));


	// ������������������
	m_IndexCount = (UINT)meshData.indexVec.size();
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = m_IndexCount * sizeof(IndexType);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	// �½�����������
	InitData.pSysMem = meshData.indexVec.data();
	HR(device->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));



}

void GameApp::GameObject::SetTexture(ComPtr<ID3D11ShaderResourceView> texture)
{
	m_pTexture = texture;
}

void GameApp::GameObject::SetWorldMatrix(const XMFLOAT4X4 & world)
{
	m_WorldMatrix = world;
}

void XM_CALLCONV GameApp::GameObject::SetWorldMatrix(FXMMATRIX world)
{
	XMStoreFloat4x4(&m_WorldMatrix, world);
}

void GameApp::GameObject::Draw(ComPtr<ID3D11DeviceContext> deviceContext)
{
	// ���ö���/����������
	UINT strides = m_VertexStride;
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &strides, &offsets);
	deviceContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	// ��ȡ֮ǰ�Ѿ��󶨵���Ⱦ�����ϵĳ����������������޸�
	ComPtr<ID3D11Buffer> cBuffer = nullptr;
	deviceContext->VSGetConstantBuffers(0, 1, cBuffer.GetAddressOf());
	CBChangesEveryDrawing cbDrawing;

	// �ڲ�����ת�ã������ⲿ�Ͳ���Ҫ��ǰת����
	XMMATRIX W = XMLoadFloat4x4(&m_WorldMatrix);
	cbDrawing.world = XMMatrixTranspose(W);
	cbDrawing.worldInvTranspose = XMMatrixInverse(nullptr, W);	// ����ת�õ���

	// ���³���������
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(deviceContext->Map(cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(CBChangesEveryDrawing), &cbDrawing, sizeof(CBChangesEveryDrawing));
	deviceContext->Unmap(cBuffer.Get(), 0);

	// ��������
	deviceContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
	// ���Կ�ʼ����
	deviceContext->DrawIndexed(m_IndexCount, 0, 0);
}

void GameApp::MyCylinder::creatCylinder(ComPtr<ID3D11Device> device, float x, float y, float z)
{
	GameObject::SetBuffer(device, Geometry::CreateCylinder());
	GameObject::SetWorldMatrix(XMMatrixTranslation(x, y, z));
	SetModel(Model(device, Geometry::CreateCylinder()));
}

DirectX::BoundingOrientedBox GameApp::MyCylinder::GetBounding() const
{
	BoundingOrientedBox box;
	BoundingOrientedBox::CreateFromBoundingBox(box, m_Model.boundingBox);
	box.Transform(box, XMLoadFloat4x4(&m_WorldMatrix));
	return box;
}

void GameApp::MySphere::creatSphere(ComPtr<ID3D11Device> device, float x, float y, float z)
{
	GameObject::SetBuffer(device, Geometry::CreateSphere());
	GameObject::SetWorldMatrix(XMMatrixTranslation(x, y, z));
}

void XM_CALLCONV GameApp::MySphere::StartMove(FXMVECTOR V)
{
	isMove = true;
	moveDir = XMVector3Normalize(V);
	speedY = 0.0f;//����Y���ٶ�
}

void GameApp::MySphere::updateMove(float dt)
{
	if (isMove&&isVisible) {
		speedY += dt * grivate*0.005f;
		SetWorldMatrix(XMLoadFloat4x4(&m_WorldMatrix)*XMMatrixTranslationFromVector(moveDir*5.0f*dt)*XMMatrixTranslationFromVector(g_XMNegIdentityR1*speedY));
		if (m_WorldMatrix._42 <= 0.0f) {
			isMove = false;
		}
	}
}

DirectX::BoundingSphere GameApp::MySphere::GetBounding() const
{
	DirectX::BoundingSphere m_BoundingSphere;
	m_BoundingSphere.Center = XMFLOAT3(m_WorldMatrix._41, m_WorldMatrix._42, m_WorldMatrix._43);
	m_BoundingSphere.Radius = 1.0f;
	return m_BoundingSphere;
}
