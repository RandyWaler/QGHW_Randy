#pragma once
//游戏计时器类

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;		// 总游戏时间
	float DeltaTime()const;		// 帧间隔时间

	void Reset(); // 在消息循环之前调用
	void Start(); // 在取消暂停的时候调用
	void Stop();  // 在暂停的时候调用
	void Tick();  // 在每一帧的时候调用

private:
	double m_SecondsPerCount; 
	double m_DeltaTime; //每次Tick() 时计算游戏中两帧的时差

	__int64 m_BaseTime;//计时器开启的时间
	__int64 m_PausedTime;//计时器暂停总时间
	__int64 m_StopTime;//计时器停止的时间
	__int64 m_PrevTime;//记录上一帧调用Tick()时的时间
	__int64 m_CurrTime;//当前时间

	bool m_Stopped;//是否暂停
};

