#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "Geometry.h"
#include "LightHelper.h"
#include "Camera.h"
#include "SkyRender.h"
#include "Collision.h"
#include "Model.h"
class GameApp : public D3DApp
{
public:

	struct CBChangesEveryDrawing
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldInvTranspose;
	};

	struct CBChangesEveryFrame
	{
		DirectX::XMMATRIX view;
		DirectX::XMFLOAT4 eyePos;
	};

	struct CBChangesOnResize
	{
		DirectX::XMMATRIX proj;
	};

	struct CBChangesRarely
	{
		DirectionalLight dirLight[10];
		PointLight pointLight[10];
		SpotLight spotLight[10];
		Material material;
		int numDirLight;
		int numPointLight;
		int numSpotLight;
		float pad;		// 打包保证16字节对齐
	};

	// 一个尽可能小的游戏对象类
	class GameObject
	{
	public:
		GameObject();

		// 获取位置
		DirectX::XMFLOAT3 GetPosition() const;
		// 设置缓冲区
		template<class VertexType, class IndexType>
		void SetBuffer(ComPtr<ID3D11Device> device, const Geometry::MeshData<VertexType, IndexType>& meshData);
		// 设置纹理
		void SetTexture(ComPtr<ID3D11ShaderResourceView> texture);
		// 设置矩阵
		void SetWorldMatrix(const DirectX::XMFLOAT4X4& world);
		void XM_CALLCONV SetWorldMatrix(DirectX::FXMMATRIX world);
		// 绘制
		virtual void Draw(ComPtr<ID3D11DeviceContext> deviceContext);
	protected:
		DirectX::XMFLOAT4X4 m_WorldMatrix;				// 世界矩阵
		ComPtr<ID3D11ShaderResourceView> m_pTexture;		// 纹理
		ComPtr<ID3D11Buffer> m_pVertexBuffer;				// 顶点缓冲区
		ComPtr<ID3D11Buffer> m_pIndexBuffer;				// 索引缓冲区
		UINT m_VertexStride;								// 顶点字节大小
		UINT m_IndexCount;								// 索引数目	
	};

	class MyCylinder : public GameObject
	{
	private:
		bool isVisible = true;
		Model m_Model;												// 模型
	public:
		void creatCylinder(ComPtr<ID3D11Device> device, float x, float y, float z);
		// 绘制
		virtual void Draw(ComPtr<ID3D11DeviceContext> deviceContext) {
			if (isVisible) {
				GameObject::Draw(deviceContext);
			}
		}
		void setIsVisible(bool s) {
			isVisible = s;
		}
		void SetModel(Model && model)
		{
			std::swap(m_Model, model);
			model.modelParts.clear();
			model.boundingBox = DirectX::BoundingBox();
		}
		bool IsVisible() {
			return isVisible;
		}
		void reSet(float x, float y, float z) {
			GameObject::SetWorldMatrix(DirectX::XMMatrixTranslation(x, y, z));
			isVisible = true;
		}
		DirectX::BoundingOrientedBox GetBounding() const;
	};
	class MySphere : public GameObject
	{
	private:
		bool isVisible = true;
		bool isMove = false;
		DirectX::XMVECTOR moveDir;
		const float grivate = 1.0f;
		float speedY = 0.0f;
		//Model m_Model;												// 模型
	public:
		void creatSphere(ComPtr<ID3D11Device> device, float x, float y, float z);
		// 绘制
		virtual void Draw(ComPtr<ID3D11DeviceContext> deviceContext) {
			if (isVisible) {
				GameObject::Draw(deviceContext);
			}
		}
		void setIsVisible(bool s) {
			isVisible = s;
		}
		//void SetModel(Model && model)
		//{
		//	std::swap(m_Model, model);
		//	model.modelParts.clear();
		//	model.boundingBox = BoundingBox();
		//}
		void XM_CALLCONV StartMove(DirectX::FXMVECTOR V);
		void updateMove(float dt);
		void endMove() {
			isMove = false;
		}
		bool IsVisible() {
			return isVisible;
		}
		void reSet(float x, float y, float z) {
			GameObject::SetWorldMatrix(DirectX::XMMatrixTranslation(x, y, z));
			isMove = false;
			isVisible = true;
		}
		DirectX::BoundingSphere GetBounding() const;
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

	void reSetGameObjEffect();

private:
	
	ComPtr<ID2D1SolidColorBrush> m_pColorBrush;				// 单色笔刷
	ComPtr<IDWriteFont> m_pFont;								// 字体
	ComPtr<IDWriteTextFormat> m_pTextFormat;					// 文本格式

	ComPtr<ID3D11InputLayout> m_pVertexLayout2D;				// 用于2D的顶点输入布局
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D;				// 用于3D的顶点输入布局
	ComPtr<ID3D11Buffer> m_pConstantBuffers[4];				// 常量缓冲区

	GameObject m_Floor;										// 地板

	MyCylinder m_Cylinder[6];                               // 圆柱体
	MySphere m_Sphere[6];

	ComPtr<ID3D11VertexShader> m_pVertexShader3D;				// 用于3D的顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader3D;				// 用于3D的像素着色器
	ComPtr<ID3D11VertexShader> m_pVertexShader2D;				// 用于2D的顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader2D;				// 用于2D的像素着色器

	CBChangesEveryFrame m_CBFrame;							// 该缓冲区存放仅在每一帧进行更新的变量
	CBChangesOnResize m_CBOnResize;							// 该缓冲区存放仅在窗口大小变化时更新的变量
	CBChangesRarely m_CBRarely;								// 该缓冲区存放不会再进行修改的变量

	ComPtr<ID3D11SamplerState> m_pSamplerState;				// 采样器状态

	std::shared_ptr<Camera> m_pCamera;						// 摄像机


	SkyEffect m_SkyEffect;									// 天空盒特效管理
	std::unique_ptr<SkyRender> m_pSunset;						// 天空盒(日落)

	std::wstring m_PickedObjStr;


	MySphere *pickingSphere;

};


#endif