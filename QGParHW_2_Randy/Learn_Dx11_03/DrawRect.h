#pragma once
class DrawRect
{
private:
	int nowState = 0;//��ǰ�׶�ֵ
	int nowPointNum = 0;//��ǰ��Ҫ���ֵĶ�������
public:

//��ʼ��
	DrawRect();
	~DrawRect();
//����
	void rectUpdate(float dt);
//Get
	int getPointNum();
};

