#pragma once
#include "LinkStack.h"
#include "Symbol.h"
#include "Main.h"
class Calculator
{
private:
	ForwardList * middleEx;//��׺ʽ
	ForwardList* backEx;//��׺ʽ
	ForwardList* backEx2;//��׺ʽ
	ForwardList* backEx3;//��׺ʽ
	LinkStack<Symbol> * symbolStack;//���ʽջ

	int strLength = 512;
public:
	//��ʼ��
	Calculator();
	~Calculator();
	void reSet();
	//�������
	void getInputEx();//��ʾ�û�����һ�����ʽ
	void changeBackEx();//����׺ʽ�任Ϊ��׺ʽ
	void Calculation();//�����׺ʽ��ֵ
	void Calculation2();//�����׺ʽ��ֵ
	void Calculation3();//�����׺ʽ��ֵ
};

