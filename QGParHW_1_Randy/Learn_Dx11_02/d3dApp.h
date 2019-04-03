#pragma once

#include <wrl/client.h> //ComPtr����ָ��ͷ�ļ�
#include <string> //�ַ�����
#include <d3d11_1.h> //D3D��
#include <DirectXMath.h> //DX��ѧ��
#include "GameTimer.h" //��ʱ����

//Direct3DӦ�ó������� 
//��WINDOWS���ڳ���Ϊ���� ���WINDOWS���ڳ�����ʱ��Ҫ����ɵĹ��� 
//����D3D�豸�Լ���ػ�������Դ��ͼ
//���D3D�豸 WINDOWS���ڳ���ĳ�ʼ������ ��Ϸ֡�ʼ�������ʾ����
//�ֶμ�¼D3DӦ�ó���Ļ�����Ϣ��������Ϸ��ͣ�����Ƿ���󻯣����ز����� 
//�ṩ��Ϣѭ�� ��Ϣ������չλ��
//Ӳ�Թ涨���ࣨ����D3DӦ�ó����ࣩ�������ÿ֡���¹��� �Լ�ÿ֡����
class D3DApp
{
public:
	//���������ٷ���------------------------------------------------------------------------------------
	D3DApp(HINSTANCE hInstance);  //D3DApp���췽����Ҫһ����ǰ����ʵ�������Ϊ��������
	virtual ~D3DApp();

	//Get����-------------------------------------------------------------------------------------------
	HINSTANCE AppInst()const; //��ȡ����ʱ���벢��¼�ĵ�ǰ����ʵ�����
	HWND MainWnd()const; //��ȡ�����ھ��
	float AspectRatio()const; //��ȡ��ǰ��Ļ�Ŀ�߱�

	//--------------------------------------------------------------------------------------------------
	int Run(); //��Ϸ����Ϣѭ��

	// ��ܷ����������ࣨGameApp����Ҫ������Щ������ʵ���ض���Ӧ������----------------------------------
	virtual bool Init(); //��ʼ�������ø��෽����Ҫ��ʼ�����ں�Direct3D���֣������ʼ����������                 
	virtual void OnResize(); // �ø��෽����Ҫ�ڴ��ڴ�С�䶯��ʱ�����
	virtual void UpdateScene(float dt) = 0; // ���������Ҫʵ�ָ÷��������ÿһ֡�ĸ���
	virtual void DrawScene() = 0; // ���������Ҫʵ�ָ÷��������ÿһ֡�Ļ���
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // ���ڵ���Ϣ�ص�����

protected:
	//����̳е��������صķ���--------------------------------------------------------------------------
	bool InitMainWindow();      // ���ڳ�ʼ������
	bool InitDirect3D();        // Direct3D��ʼ������

	void CalculateFrameStats(); // ����ÿ��֡�����ڴ�����ʾ��Ӧ�ó��򴰿����Ϸ���ÿ��֡����ʾ��

protected:
	//����ֶ�------------------------------------------------------------------------------------------
	HINSTANCE m_hAppInst;        // Ӧ��ʵ�����
	HWND      m_hMainWnd;        // �����ھ��
	bool      m_AppPaused;       // Ӧ���Ƿ���ͣ
	bool      m_Minimized;       // Ӧ���Ƿ���С��
	bool      m_Maximized;       // Ӧ���Ƿ����
	bool      m_Resizing;        // ���ڴ�С�Ƿ�仯
	bool      m_Enable4xMsaa;    // �Ƿ���4�����ز���
	UINT      m_4xMsaaQuality;   // MSAA֧�ֵ������ȼ�

	GameTimer m_Timer;           // ��ʱ��

	// ʹ��ģ�����(C++11)��������
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	// Direct3D 11
	ComPtr<ID3D11Device> m_pd3dDevice;                    // D3D11�豸
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;   // D3D11�豸������
	ComPtr<IDXGISwapChain> m_pSwapChain;                  // D3D11������
	// Direct3D 11.1
	ComPtr<ID3D11Device1> m_pd3dDevice1;                  // D3D11.1�豸
	ComPtr<ID3D11DeviceContext1> m_pd3dImmediateContext1; // D3D11.1�豸������
	ComPtr<IDXGISwapChain1> m_pSwapChain1;                // D3D11.1������
    // ������Դ
	ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;        // ���ģ�建����
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;   // ���ģ����ͼ �����/ģ�建�����󶨵���Ⱦ������
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;   // ��ȾĿ����ͼ ����̨�������󶨵���������ϲ����׶�
	D3D11_VIEWPORT m_ScreenViewport;                      // �ӿ�

    // ������Ӧ���ڹ��캯�����ú���Щ�Զ���ĳ�ʼ����---------------------------------------------------
	std::wstring m_MainWndCaption;                       // �����ڱ���
	int m_ClientWidth;                                   // �ӿڿ��
	int m_ClientHeight;                                  // �ӿڸ߶�
	//����D3DӦ�ó������಻�������ֶεĶ���
};

