#pragma once
#include "LinkStack.h"
#include "Symbol.h"
#include "Main.h"
class Calculator
{
private:
	ForwardList * middleEx;//��׺ʽ
	ForwardList* backEx;//��׺ʽ
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
};

