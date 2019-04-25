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
		float pad;		// �����֤16�ֽڶ���
	};

	// һ��������С����Ϸ������
	class GameObject
	{
	public:
		GameObject();

		// ��ȡλ��
		DirectX::XMFLOAT3 GetPosition() const;
		// ���û�����
		template<class VertexType, class IndexType>
		void SetBuffer(ComPtr<ID3D11Device> device, const Geometry::MeshData<VertexType, IndexType>& meshData);
		// ��������
		void SetTexture(ComPtr<ID3D11ShaderResourceView> texture);
		// ���þ���
		void SetWorldMatrix(const DirectX::XMFLOAT4X4& world);
		void XM_CALLCONV SetWorldMatrix(DirectX::FXMMATRIX world);
		// ����
		virtual void Draw(ComPtr<ID3D11DeviceContext> deviceContext);
	protected:
		DirectX::XMFLOAT4X4 m_WorldMatrix;				// �������
		ComPtr<ID3D11ShaderResourceView> m_pTexture;		// ����
		ComPtr<ID3D11Buffer> m_pVertexBuffer;				// ���㻺����
		ComPtr<ID3D11Buffer> m_pIndexBuffer;				// ����������
		UINT m_VertexStride;								// �����ֽڴ�С
		UINT m_IndexCount;								// ������Ŀ	
	};

	class MyCylinder : public GameObject
	{
	private:
		bool isVisible = true;
		Model m_Model;												// ģ��
	public:
		void creatCylinder(ComPtr<ID3D11Device> device, float x, float y, float z);
		// ����
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
		//Model m_Model;												// ģ��
	public:
		void creatSphere(ComPtr<ID3D11Device> device, float x, float y, float z);
		// ����
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
	
	ComPtr<ID2D1SolidColorBrush> m_pColorBrush;				// ��ɫ��ˢ
	ComPtr<IDWriteFont> m_pFont;								// ����
	ComPtr<IDWriteTextFormat> m_pTextFormat;					// �ı���ʽ

	ComPtr<ID3D11InputLayout> m_pVertexLayout2D;				// ����2D�Ķ������벼��
	ComPtr<ID3D11InputLayout> m_pVertexLayout3D;				// ����3D�Ķ������벼��
	ComPtr<ID3D11Buffer> m_pConstantBuffers[4];				// ����������

	GameObject m_Floor;										// �ذ�

	MyCylinder m_Cylinder[6];                               // Բ����
	MySphere m_Sphere[6];

	ComPtr<ID3D11VertexShader> m_pVertexShader3D;				// ����3D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> m_pPixelShader3D;				// ����3D��������ɫ��
	ComPtr<ID3D11VertexShader> m_pVertexShader2D;				// ����2D�Ķ�����ɫ��
	ComPtr<ID3D11PixelShader> m_pPixelShader2D;				// ����2D��������ɫ��

	CBChangesEveryFrame m_CBFrame;							// �û�������Ž���ÿһ֡���и��µı���
	CBChangesOnResize m_CBOnResize;							// �û�������Ž��ڴ��ڴ�С�仯ʱ���µı���
	CBChangesRarely m_CBRarely;								// �û�������Ų����ٽ����޸ĵı���

	ComPtr<ID3D11SamplerState> m_pSamplerState;				// ������״̬

	std::shared_ptr<Camera> m_pCamera;						// �����


	SkyEffect m_SkyEffect;									// ��պ���Ч����
	std::unique_ptr<SkyRender> m_pSunset;						// ��պ�(����)

	std::wstring m_PickedObjStr;


	MySphere *pickingSphere;

};


#endif