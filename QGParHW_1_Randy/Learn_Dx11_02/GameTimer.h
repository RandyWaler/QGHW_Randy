#pragma once
//��Ϸ��ʱ����

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;		// ����Ϸʱ��
	float DeltaTime()const;		// ֡���ʱ��

	void Reset(); // ����Ϣѭ��֮ǰ����
	void Start(); // ��ȡ����ͣ��ʱ�����
	void Stop();  // ����ͣ��ʱ�����
	void Tick();  // ��ÿһ֡��ʱ�����

private:
	double m_SecondsPerCount; 
	double m_DeltaTime; //ÿ��Tick() ʱ������Ϸ����֡��ʱ��

	__int64 m_BaseTime;//��ʱ��������ʱ��
	__int64 m_PausedTime;//��ʱ����ͣ��ʱ��
	__int64 m_StopTime;//��ʱ��ֹͣ��ʱ��
	__int64 m_PrevTime;//��¼��һ֡����Tick()ʱ��ʱ��
	__int64 m_CurrTime;//��ǰʱ��

	bool m_Stopped;//�Ƿ���ͣ
};

