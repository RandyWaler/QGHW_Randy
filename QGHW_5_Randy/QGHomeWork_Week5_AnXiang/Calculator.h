#pragma once
#include "LinkStack.h"
#include "Symbol.h"
#include "LinkBinaryTree.h"
#include<iostream>
#include<stdlib.h>
#include<string>
#include<stack>
class Calculator
{
private:
	ForwardList * middleEx;//中缀式
	Symbol* symbolMiddleEx;//中缀式
	ForwardList* frontEx;//前缀式
	LinkStack<Symbol> * symbolStack;//表达式栈
	LinkStack<Symbol> * symbolStack2;//表达式栈
	static LinkBinaryTree<Symbol*>* symbolTree;


	int strLength = 512;

	static int exSize;

	static int arryFlag;
public:
	//初始化
	Calculator();
	~Calculator();
	void reSet();
	//功能相关
	void getInputEx();//提示用户输入一个表达式
	void changeFrontEx();//由中缀式变换为前缀式
	void changeTree();//由前缀式变为树
	void Calculation();//计算后缀式的值

	static void CalCulationTree(LinkBinaryTree<Symbol*>::EleNode* eNode);
};

void checkSymbol(Symbol* sym);


