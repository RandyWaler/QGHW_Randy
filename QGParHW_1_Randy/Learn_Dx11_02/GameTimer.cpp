#include "GameTimer.h"
#include <windows.h>


GameTimer::GameTimer()
	: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_BaseTime(0),
	m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec; //��¼ÿ��Countֵ��CPUʱ��ÿ������Ƶ�ʣ� ��ΪCout->Sceonds ��ת������
}

float GameTimer::TotalTime()const //������Ϸʱ�䣨��������ͣʱ�����Ϸ����ʱ�䣩
{

	if (m_Stopped)//����Ϸ��ͣ ��Ϸ��ʱ������ͣʱ�� ��ȥ֮ǰ��ͣ��ʱ�� ����Ϸ��ʼ����ʱ�� ��ת������
	{
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
	else//����Ϸû����ͣ ��Ϸ��ʱ���ǵ�ǰ֡��ʱ�̼�֮ǰ��ͣ��ʱ�� ����Ϸ��ʼ����ʱ�� ��ת������
	{
		return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
}

float GameTimer::DeltaTime()const//��õ�ǰ֡����һ֡��ʱ���ֵ
{
	return (float)m_DeltaTime;
}

void GameTimer::Reset()//���ü�ʱ��
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_PausedTime = 0;	// �漰�����Reset�Ļ���Ҫ�����0
	m_Stopped = false;
}

void GameTimer::Start()//������ʱ��
{
	__int64 startTime; //��¼������ʱ����ʱ��
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_Stopped) //����ʱ��������ͣ״̬������ʱ��
	{
		m_PausedTime += (startTime - m_StopTime);//�����ε���ͣʱ���ۼӵ���ͣ��ʱ��

		m_PrevTime = startTime; //��һ֡ʱ���Ϊ����ʱ��
		m_StopTime = 0;
		m_Stopped = false;
	}
}

void GameTimer::Stop()//��ͣ��ʱ��
{
	if (!m_Stopped)//����ͣ״̬������ͣ��ʱ��
	{
		__int64 currTime;//ˢ��CurTime
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;//��¼ֹͣʱ��
		m_Stopped = true;
	}
}

void GameTimer::Tick()//ÿ֡����
{
	if (m_Stopped)//��ͣʱ����0.0f
	{
		m_DeltaTime = 0.0;
		return;
	}

	__int64 currTime;//ˢ��CurTime
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount; //���������֮֡���ʱ���


	m_PrevTime = m_CurrTime;//ˢ��PreTime Ϊ��һ֡����ʱ����׼��

	if (m_DeltaTime < 0.0)//���д������л��ᵼ��ʱ����Ϊ��ֵ ��ʱӦУ��Ϊ0
	{
		m_DeltaTime = 0.0;
	}
}
