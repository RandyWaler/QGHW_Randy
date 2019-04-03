#pragma once

#include <wrl/client.h> //ComPtr智能指针头文件
#include <string> //字符串库
#include <d3d11_1.h> //D3D库
#include <DirectXMath.h> //DX数学库
#include "GameTimer.h" //计时器类

//Direct3D应用程序框架类 
//以WINDOWS窗口程序为基础 完成WINDOWS窗口程序定义时需要的完成的工作 
//链接D3D设备以及相关缓冲区资源视图
//完成D3D设备 WINDOWS窗口程序的初始化工作 游戏帧率计算与显示工作
//字段记录D3D应用程序的基本信息（包括游戏暂停窗口是否最大化，多重采样） 
//提供消息循环 消息处理扩展位置
//硬性规定子类（具体D3D应用程序类）必须完成每帧更新工作 以及每帧绘制
class D3DApp
{
public:
	//构造与销毁方法------------------------------------------------------------------------------------
	D3DApp(HINSTANCE hInstance);  //D3DApp构造方法需要一个当前程序实例句柄作为参数传入
	virtual ~D3DApp();

	//Get方法-------------------------------------------------------------------------------------------
	HINSTANCE AppInst()const; //获取构造时传入并记录的当前程序实例句柄
	HWND MainWnd()const; //获取主窗口句柄
	float AspectRatio()const; //获取当前屏幕的宽高比

	//--------------------------------------------------------------------------------------------------
	int Run(); //游戏主消息循环

	// 框架方法，派生类（GameApp）需要重载这些方法以实现特定的应用需求----------------------------------
	virtual bool Init(); //初始化方法该父类方法需要初始化窗口和Direct3D部分，子类初始化其他部分                 
	virtual void OnResize(); // 该父类方法需要在窗口大小变动的时候调用
	virtual void UpdateScene(float dt) = 0; // 子类必须需要实现该方法，完成每一帧的更新
	virtual void DrawScene() = 0; // 子类必须需要实现该方法，完成每一帧的绘制
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // 窗口的消息回调函数

protected:
	//子类继承但不必重载的方法--------------------------------------------------------------------------
	bool InitMainWindow();      // 窗口初始化方法
	bool InitDirect3D();        // Direct3D初始化方法

	void CalculateFrameStats(); // 计算每秒帧数并在窗口显示（应用程序窗口最上方的每秒帧率显示）

protected:
	//相关字段------------------------------------------------------------------------------------------
	HINSTANCE m_hAppInst;        // 应用实例句柄
	HWND      m_hMainWnd;        // 主窗口句柄
	bool      m_AppPaused;       // 应用是否暂停
	bool      m_Minimized;       // 应用是否最小化
	bool      m_Maximized;       // 应用是否最大化
	bool      m_Resizing;        // 窗口大小是否变化
	bool      m_Enable4xMsaa;    // 是否开启4倍多重采样
	UINT      m_4xMsaaQuality;   // MSAA支持的质量等级

	GameTimer m_Timer;           // 计时器

	// 使用模板别名(C++11)简化类型名
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	// Direct3D 11
	ComPtr<ID3D11Device> m_pd3dDevice;                    // D3D11设备
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;   // D3D11设备上下文
	ComPtr<IDXGISwapChain> m_pSwapChain;                  // D3D11交换链
	// Direct3D 11.1
	ComPtr<ID3D11Device1> m_pd3dDevice1;                  // D3D11.1设备
	ComPtr<ID3D11DeviceContext1> m_pd3dImmediateContext1; // D3D11.1设备上下文
	ComPtr<IDXGISwapChain1> m_pSwapChain1;                // D3D11.1交换链
    // 常用资源
	ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;        // 深度模板缓冲区
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;   // 深度模板视图 将深度/模板缓冲区绑定到渲染管线上
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;   // 渲染目标视图 将后台缓冲区绑定到管线输出合并器阶段
	D3D11_VIEWPORT m_ScreenViewport;                      // 视口

    // 派生类应该在构造函数设置好这些自定义的初始参数---------------------------------------------------
	std::wstring m_MainWndCaption;                       // 主窗口标题
	int m_ClientWidth;                                   // 视口宽度
	int m_ClientHeight;                                  // 视口高度
	//这里D3D应用程序框架类不做上述字段的定义
};

