#pragma once
#include "LinkStack.h"
#include "Symbol.h"
#include "Main.h"
class Calculator
{
private:
	ForwardList * middleEx;//中缀式
	ForwardList* backEx;//后缀式
	ForwardList* backEx2;//后缀式
	ForwardList* backEx3;//后缀式
	LinkStack<Symbol> * symbolStack;//表达式栈

	int strLength = 512;
public:
	//初始化
	Calculator();
	~Calculator();
	void reSet();
	//功能相关
	void getInputEx();//提示用户输入一个表达式
	void changeBackEx();//由中缀式变换为后缀式
	void Calculation();//计算后缀式的值
	void Calculation2();//计算后缀式的值
	void Calculation3();//计算后缀式的值
};

