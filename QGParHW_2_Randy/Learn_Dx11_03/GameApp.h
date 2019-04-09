#pragma once
//游戏应用程序扩展类 游戏逻辑的实现
#include "d3dApp.h"



class GameApp : public D3DApp
{
public:
	struct VertexPosColor //创建与结构体对应的输入结构体
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};
	struct ConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
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

	UINT idexBuffer;
	UINT vertexBuffers;

	const float moveRect = 3.0f;//移动限制
	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// 顶点输入布局
	ComPtr<ID3D11Buffer> m_pVertexBuffer;			// 顶点缓冲区
	ComPtr<ID3D11Buffer> m_pIndexBuffer;			// 索引缓冲区
	ComPtr<ID3D11Buffer> m_pConstantBuffer;		// 常量缓冲区

	ComPtr<ID3D11VertexShader> m_pVertexShader;	// 顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader;		// 像素着色器
	ConstantBuffer m_CBuffer;	// 用于修改GPU常量缓冲区的变量




};

