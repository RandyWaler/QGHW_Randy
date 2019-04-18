#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "Geometry.h"
#include "LightHelper.h"

enum NowPlayType
{
	Cube00,
	Anima,
	Cube01
};

class GameApp : public D3DApp
{
public:
	struct VSConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
		DirectX::XMMATRIX worldInvTranspose;
	};

	struct PSConstantBuffer
	{
		DirectionalLight dirLight;
		Material material;
		DirectX::XMFLOAT4 eyePos;
	};

	struct PSConstantBufferRotate
	{
		DirectX::XMMATRIX rotate;
	};


public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();


private:
	bool InitEffect();
	bool InitResource();

	template<class VertexType>
	bool ResetMesh(const Geometry::MeshData<VertexType>& meshData);
	const float moveRect = 3.0f;//�ƶ�����
	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;

private:
	
	ComPtr<ID2D1SolidColorBrush> m_pColorBrush;				// ��ɫ��ˢ
	ComPtr<IDWriteFont> m_pFont;								// ����
	ComPtr<IDWriteTextFormat> m_pTextFormat;					// �ı���ʽ

	ComPtr<ID3D11InputLayout> m_pVertexLayout2D;				// ����2D�Ķ������벼��
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D;				// ����3D�Ķ������벼��
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D2;				// ����3D�Ķ������벼��
	ComPtr<ID3D11Buffer> m_pVertexBuffer;						// ���㻺����
	ComPtr<ID3D11Buffer> m_pIndexBuffer;						// ����������
	ComPtr<ID3D11Buffer> m_pConstantBuffers[3];				// ����������
	UINT m_IndexCount;										// ������������������С
	int m_CurrFrame;											// ��ǰ���涯�����ŵ��ڼ�֡


	ComPtr<ID3D11ShaderResourceView> m_pCubeTex[6];			// ľ������

	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pFireAnims;// ��������

	ComPtr<ID3D11ShaderResourceView> m_proCubeTex;			// ������ת����ʹ������
	ComPtr<ID3D11ShaderResourceView> m_proCubeTex2;			



	ComPtr<ID3D11SamplerState> m_pSamplerState;				// ������״̬

	ComPtr<ID3D11VertexShader> m_pVertexShader3D;				// ����3D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> m_pPixelShader3D;				// ����3D��������ɫ��

	ComPtr<ID3D11VertexShader> m_pVertexShader3D2;				// ����3D�Ķ�����ɫ��  ���ڻ����޹��յ�Cube
	ComPtr<ID3D11PixelShader> m_pPixelShader3D2;				// ����3D��������ɫ��

	ComPtr<ID3D11VertexShader> m_pVertexShader2D;				// ����2D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> m_pPixelShader2D;				// ����2D��������ɫ��

	VSConstantBuffer m_VSConstantBuffer;						// �����޸�����VS��GPU�����������ı���
	PSConstantBuffer m_PSConstantBuffer;						// �����޸�����PS��GPU�����������ı���
	PSConstantBufferRotate m_PSConstantBufferRotate;




	DirectionalLight m_DirLight;					// Ĭ�ϻ�����

	NowPlayType nowType;

};


#endif