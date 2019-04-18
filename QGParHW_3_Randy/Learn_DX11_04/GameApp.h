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
	const float moveRect = 3.0f;//移动限制
	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;

private:
	
	ComPtr<ID2D1SolidColorBrush> m_pColorBrush;				// 单色笔刷
	ComPtr<IDWriteFont> m_pFont;								// 字体
	ComPtr<IDWriteTextFormat> m_pTextFormat;					// 文本格式

	ComPtr<ID3D11InputLayout> m_pVertexLayout2D;				// 用于2D的顶点输入布局
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D;				// 用于3D的顶点输入布局
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D2;				// 用于3D的顶点输入布局
	ComPtr<ID3D11Buffer> m_pVertexBuffer;						// 顶点缓冲区
	ComPtr<ID3D11Buffer> m_pIndexBuffer;						// 索引缓冲区
	ComPtr<ID3D11Buffer> m_pConstantBuffers[3];				// 常量缓冲区
	UINT m_IndexCount;										// 绘制物体的索引数组大小
	int m_CurrFrame;											// 当前火焰动画播放到第几帧


	ComPtr<ID3D11ShaderResourceView> m_pCubeTex[6];			// 木盒纹理

	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pFireAnims;// 火焰纹理集

	ComPtr<ID3D11ShaderResourceView> m_proCubeTex;			// 纹理旋转动画使用纹理
	ComPtr<ID3D11ShaderResourceView> m_proCubeTex2;			



	ComPtr<ID3D11SamplerState> m_pSamplerState;				// 采样器状态

	ComPtr<ID3D11VertexShader> m_pVertexShader3D;				// 用于3D的顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader3D;				// 用于3D的像素着色器

	ComPtr<ID3D11VertexShader> m_pVertexShader3D2;				// 用于3D的顶点着色器  用于绘制无光照的Cube
	ComPtr<ID3D11PixelShader> m_pPixelShader3D2;				// 用于3D的像素着色器

	ComPtr<ID3D11VertexShader> m_pVertexShader2D;				// 用于2D的顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader2D;				// 用于2D的像素着色器

	VSConstantBuffer m_VSConstantBuffer;						// 用于修改用于VS的GPU常量缓冲区的变量
	PSConstantBuffer m_PSConstantBuffer;						// 用于修改用于PS的GPU常量缓冲区的变量
	PSConstantBufferRotate m_PSConstantBufferRotate;




	DirectionalLight m_DirLight;					// 默认环境光

	NowPlayType nowType;

};


#endif