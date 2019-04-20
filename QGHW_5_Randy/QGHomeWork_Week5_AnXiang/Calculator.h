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
	ForwardList * middleEx;//��׺ʽ
	Symbol* symbolMiddleEx;//��׺ʽ
	ForwardList* frontEx;//ǰ׺ʽ
	LinkStack<Symbol> * symbolStack;//���ʽջ
	LinkStack<Symbol> * symbolStack2;//���ʽջ
	static LinkBinaryTree<Symbol*>* symbolTree;


	int strLength = 512;

	static int exSize;

	static int arryFlag;
public:
	//��ʼ��
	Calculator();
	~Calculator();
	void reSet();
	//�������
	void getInputEx();//��ʾ�û�����һ�����ʽ
	void changeFrontEx();//����׺ʽ�任Ϊǰ׺ʽ
	void changeTree();//��ǰ׺ʽ��Ϊ��
	void Calculation();//�����׺ʽ��ֵ

	static void CalCulationTree(LinkBinaryTree<Symbol*>::EleNode* eNode);
};

void checkSymbol(Symbol* sym);


