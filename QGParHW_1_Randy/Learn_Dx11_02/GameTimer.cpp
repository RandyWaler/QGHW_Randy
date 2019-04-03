#include "GameTimer.h"
#include <windows.h>


GameTimer::GameTimer()
	: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_BaseTime(0),
	m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec; //记录每秒Count值（CPU时钟每秒运行频率） 作为Cout->Sceonds 的转换因子
}

float GameTimer::TotalTime()const //返回游戏时间（不包括暂停时间的游戏运行时间）
{

	if (m_Stopped)//若游戏暂停 游戏总时间是暂停时刻 减去之前暂停总时长 和游戏开始运行时刻 乘转换因子
	{
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
	else//若游戏没有暂停 游戏总时间是当前帧的时刻减之前暂停总时长 和游戏开始运行时刻 乘转换因子
	{
		return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
}

float GameTimer::DeltaTime()const//获得当前帧和上一帧的时间差值
{
	return (float)m_DeltaTime;
}

void GameTimer::Reset()//重置计时器
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_PausedTime = 0;	// 涉及到多次Reset的话需要将其归0
	m_Stopped = false;
}

void GameTimer::Start()//开启计时器
{
	__int64 startTime; //记录开启计时器的时刻
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_Stopped) //若计时器处于暂停状态开启计时器
	{
		m_PausedTime += (startTime - m_StopTime);//将本次的暂停时长累加到暂停总时长

		m_PrevTime = startTime; //上一帧时间变为开启时间
		m_StopTime = 0;
		m_Stopped = false;
	}
}

void GameTimer::Stop()//暂停计时器
{
	if (!m_Stopped)//非暂停状态调用暂停计时器
	{
		__int64 currTime;//刷新CurTime
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;//记录停止时刻
		m_Stopped = true;
	}
}

void GameTimer::Tick()//每帧调用
{
	if (m_Stopped)//暂停时返回0.0f
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;//刷新CurTime
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount; //计算和上以帧之间的时间差


	m_PrevTime = m_CurrTime;//刷新PreTime 为下一帧计算时差做准备

	if (m_DeltaTime < 0.0)//若有处理器切换会导致时间差变为负值 此时应校正为0
	{
		m_DeltaTime = 0.0;
	}
}
