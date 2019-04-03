#pragma once
//��ϷӦ�ó�����չ�� ��Ϸ�߼���ʵ��
#include "d3dApp.h"
class GameApp : public D3DApp
{
public:
	struct VertexPosColor //������ṹ���Ӧ������ṹ��
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
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

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// �������벼��
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		// ���㻺����
	ComPtr<ID3D11VertexShader> m_pVertexShader;	// ������ɫ��
	ComPtr<ID3D11PixelShader> m_pPixelShader;	// ������ɫ��

};

