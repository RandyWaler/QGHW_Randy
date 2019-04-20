#pragma once
#include "stdafx.h"

#include"Symbol.h"

#include <stack>

using namespace std;
using namespace symbolEle;

template<class T>
class LinkBinaryTree {
public:
	//�ڵ�
	struct EleNode
	{
		T eleValue;
		EleNode* left;
		EleNode* right;
	};


protected:
	TreeEleType eleType;
	EleNode *root;
	EleNode* getNewEleNode(T value) {
		EleNode* newNode = (EleNode*)malloc(sizeof(EleNode));
		if (newNode) {
			newNode->eleValue = (T)value;
			newNode->left = nullptr;
			newNode->right = nullptr;
			return newNode;
		}
		cerr << "Error���޷���ȡ�ѿռ䣡����\n" << endl;
		return nullptr;
	}

	void reMoveEleNode(EleNode* eNode);

	//stack<LinkBinaryTree<T>::EleNode*>* eNodeStack;
public:

	//void(*eNodeFuntion)(EleNode* eNode);

    LinkBinaryTree(TreeEleType type);
	~LinkBinaryTree();
	EleNode* getNodeAt(const char* pos) {
		if (pos[0] != '0') {
			cerr << "\nError��������������У�����\n" << endl;
			return nullptr;
		}
		EleNode* cur = root;

		for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
			if (!cur) {
				cerr << "\nError��������������У�����\n" << endl;
				return nullptr;
			}
			if (pos[i] == '0') {
				cur = cur->left;
			}
			else if (pos[i] == '1') {
				cur = cur->right;
			}
			else
			{
				cerr << "\nError��������������У������������\n" << endl;
				return nullptr;
			}
		}
		return cur;
	}

	T getValueAt(const char* pos);

	bool addEleTo(const char* pos, T ele, bool isReplace);
	
	bool removeEleAt(const char* pos,bool isBreak);//char* pos�������� bool isBreak�Ƿ�ǿ�ƽ�֦ 

	void removeFrmoNode(EleNode* sNode,bool issaveStart);//��ĳ����ʼ�ڵ㿪ʼɾ�� �Ƿ�����ʼ��


	void ClearTree();

	TreeEleType getTreeEleType();

	//void seteNodeFuntion(void(*fun)(EleNode* eNode));
	
	static void doThisFun(LinkBinaryTree<T>* tree,EleNode * eNode, const char * doFun);

//�ݹ�ʵ��---------------------------------------------------------------------------------------------------------
	static void PreOrderTraverse(EleNode* curNude, void(*fun)(T eValue));//��ÿ��ֵ�ķ���
	static void InOrderTraverse(EleNode* curNude, void(*fun)(T eValue));
	static void PostOrderTraverse(EleNode* curNude, void(*fun)(T eValue));

	static void PreOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);//��ÿ���ڵ�ķ���
	static void InOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);
	static void PostOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);

	static void PostOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
	static void InOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
	static void PreOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
//�ǵݹ�ʵ��-------------------------------------------------------------------------------------------------------
	static void InOrderTraverseWithStack(EleNode* curNude, void(*fun)(T eValue));
};

template<class T>
inline LinkBinaryTree<T>::LinkBinaryTree(TreeEleType type)
{
	eleType = type;
	if (eleType == TreeEleType::Num) {
		root = getNewEleNode((T)INT_MIN);
		if (!root) {
			cerr << "\nError���޷���ȡ�ѿռ�\n" << endl;
			return;
		}
	}
	else
	{
		root = getNewEleNode((T)nullptr);
		if (!root) {
			cerr << "\nError���޷���ȡ�ѿռ�\n" << endl;
			return;
		}
	}
	
	//eNodeStack = new stack<LinkBinaryTree<T>::EleNode*>();
}

template<class T>
inline LinkBinaryTree<T>::~LinkBinaryTree()
{
	ClearTree();
	reMoveEleNode(root);
	
}

template<class T>
inline T LinkBinaryTree<T>::getValueAt(const char * pos)
{
	if (pos[0] != '0') {
		cerr << "\nError��������������У�����\n" << endl;
		if (eleType == TreeEleType::Num) {
			return (T)INT_MIN;
		}
		else
		{
			return (T)nullptr;
		}
	}
	EleNode* cur = root;

	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (!cur) {
			cerr << "\nError��������������У�����\n" << endl;
			if (eleType == TreeEleType::Num) {
				return (T)INT_MIN;
			}
			else
			{
				return (T)nullptr;
			}
		}
		if (pos[i] == '0') {
			cur = cur->left;
		}
		else if (pos[i] == '1') {
			cur = cur->right;
		}
		else
		{
			cerr << "\nError��������������У������������\n" << endl;
			if (eleType == TreeEleType::Num) {
				return (T)INT_MIN;
			}
			else
			{
				return (T)nullptr;
			}
		}
	}
	if (!cur) {
		cerr << "\nError��������������У�����\n" << endl;
		if (eleType == TreeEleType::Num) {
			return (T)INT_MIN;
		}
		else
		{
			return (T)nullptr;
		}
	}
	return cur->eleValue;
}

template<class T>
inline bool LinkBinaryTree<T>::addEleTo(const char * pos, T ele, bool isReplace)
{
	if (pos[0] != '0') {
		cerr << "\nError��������������У�����\n" << endl;
		return false;
	}
	EleNode* cur = root;
	EleNode** pre;

	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (!cur) {
			cerr << "\nError��������������У�����\n" << endl;
			return false;
		}
		if (pos[i] == '0') {
			pre = &cur->left;
			cur = cur->left;
		}else if(pos[i]=='1'){
			pre = &cur->right;
			cur = cur->right;
		}
		else
		{
			cerr << "\nError��������������У������������\n" << endl;
			return false;
		}
	}
	if (cur == root) {//���ڵ����
		if (eleType == TreeEleType::Num) {
			if (root->eleValue == (T)INT_MIN) {
				root->eleValue = ele;
				return true;
			}
			else if (isReplace) {
				root->eleValue = ele;
				return true;
			}
			else
			{
				cout << "\nError�����ڵ���룬Ԫ���Ѵ���Ȩ�޲��㣡����\n" << endl;
				return false;
			}
		}
		else
		{
			if (root->eleValue == (T)nullptr) {
				root->eleValue = ele;
				return true;
			}
			else if (isReplace) {
				root->eleValue = ele;
				return true;
			}
			else
			{
				cout << "\nError�����ڵ���룬Ԫ���Ѵ���Ȩ�޲��㣡����\n" << endl;
				return false;
			}
		}
	}else {
		if (!cur) {//��λ����һ���սڵ�
			cur = getNewEleNode(ele);
			if(cur){
				*pre = cur;
			}
			return false;
		}
		else if(isReplace)
		{
			EleNode* newNode = getNewEleNode(ele);
			newNode->left = cur->left;
			newNode->right = cur->right;
			*pre = newNode;
			reMoveEleNode(cur);
			return true;
		}
		else
		{
			cerr << "Error����λ�����нڵ㣬Ȩ�޲��㣡����" << endl;
			return false;
		}
	}

}

template<class T>
inline bool LinkBinaryTree<T>::removeEleAt(const char * pos, bool isBreak)
{
	if (pos[0] != '0') {
		cerr << "\n������������У�����\n" << endl;
		return false;
	}
	EleNode* cur = root;//Ҫɾ���Ľڵ�
	EleNode** pre;//ָ��cur��ָ���ָ��
	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (!cur) {
			cerr << "\n������������У�����ָ��սڵ㣬�޷���������\n" << endl;
			return false;
		}
		if (pos[i] == '0') {
			pre = &cur->left;
			cur = cur->left;
		}
		else if (pos[i] == '1') {
			pre = &cur->right;
			cur = cur->right;
		}
		else
		{
			cerr << "\n������������У������쳣�ַ�\n" << endl;
			return false;
		}
	}
	if (cur == root) {
		cerr << "\n������������У���������ɾ�����ڵ�" << endl;
		return false;
	}
	if (!cur) {
		cerr << "\n��λ��û��Ԫ�أ�����" << endl;
		return true;
	}

    if (isBreak) {//ǿ�ƽ�֦
		removeFrmoNode(cur,false);
		*pre = nullptr;
		return true;
	}
	else if (cur->left == nullptr&&cur->right == nullptr) {
		reMoveEleNode(cur);
		*pre = nullptr;
		return true;
	}
	else
	{
		cerr << "\n������������У���������ɾ���л���֦Ҷ�Ľڵ㣬�����Ȩ��" << endl;
		return false;
	}
	
}

template<class T>
inline void LinkBinaryTree<T>::removeFrmoNode(EleNode* sNode, bool issaveStart)
{
	
	PostOrderTraverse(this,sNode->left,"removeNode");
	PostOrderTraverse(this, sNode->left, "removeNode");
	if (!issaveStart) {
		reMoveEleNode(sNode);
	}
	else {
		sNode->left = nullptr;
		sNode->right = nullptr;
	}

}

template<class T>
inline void LinkBinaryTree<T>::reMoveEleNode(EleNode* eNode)
{
	if (eNode) {
		if (eleType == TreeEleType::Ptr) {
			if (eNode->eleValue) {
				free((void*)eNode->eleValue);
			}
		}
		free(eNode);
	}
}

template<class T>
inline void LinkBinaryTree<T>::ClearTree()
{
	removeFrmoNode(root, true);
	if (eleType == TreeEleType::Num) {
		root->eleValue = (T)INT_MIN;
		root->left = nullptr;
		root->right = nullptr;
	}
	else {
		if (root->eleValue) {
			free((void*)root->eleValue);
		}
		root->eleValue = (T)nullptr;
		root->left = nullptr;
		root->right = nullptr;
	}
}

template<class T>
inline TreeEleType LinkBinaryTree<T>::getTreeEleType()
{
	return eleType;
}

//template<class T>
//inline void LinkBinaryTree<T>::seteNodeFuntion(void(*fun)(EleNode *eNode))
//{
//	eNodeFuntion = fun;
//}

template<class T>
inline void LinkBinaryTree<T>::doThisFun(LinkBinaryTree<T>* tree, EleNode * eNode, const char * doFun)
{
	if (strcmp(doFun, "removeNode")) {
		tree->reMoveEleNode(eNode);
	}
}


template<class T>
inline void LinkBinaryTree<T>::PreOrderTraverse(EleNode * curNude, void(*fun)(T eValue))
{
	if (curNude != nullptr) {
		fun(curNude->eleValue);
		PreOrderTraverse(curNude->left, fun);
		PreOrderTraverse(curNude->right, fun);
	}
}

template<class T>
inline void LinkBinaryTree<T>::InOrderTraverse(EleNode * curNude, void(*fun)(T eValue))
{
	if (curNude != nullptr) {	
		InOrderTraverse(curNude->left, fun);
		fun(curNude->eleValue);
		InOrderTraverse(curNude->right, fun);
	}
}

template<class T>
inline void LinkBinaryTree<T>::PostOrderTraverse(EleNode * curNude, void(*fun)(T eValue))
{
	if (curNude != nullptr) {
		PostOrderTraverse(curNude->left, fun);
		PostOrderTraverse(curNude->right, fun);
		fun(curNude->eleValue);
	}
}

template<class T>
inline void LinkBinaryTree<T>::PreOrderTraverse(LinkBinaryTree<T>* tree, EleNode * curNude,const char* doFun)
{
	if (curNude != nullptr) {
		doThisFun(tree,curNude, doFun);
		PreOrderTraverse(tree,curNude->left, doFun);
		PreOrderTraverse(tree, curNude->right, doFun);
	}
}


template<class T>
inline void LinkBinaryTree<T>::InOrderTraverse(LinkBinaryTree<T>* tree, EleNode * curNude, const char* doFun)
{
	if (curNude != nullptr) {
		InOrderTraverse(tree, curNude->left, doFun);
		doThisFun(tree,curNude, doFun);
		InOrderTraverse(tree, curNude->right, doFun);
	}
}

template<class T>
inline void LinkBinaryTree<T>::PostOrderTraverse(LinkBinaryTree<T>* tree, EleNode * curNude, const char* doFun)
{
	if (curNude != nullptr) {
		PostOrderTraverse(tree, curNude->left, doFun);
		PostOrderTraverse(tree, curNude->right, doFun);
		doThisFun(tree,curNude, doFun);
	}
}

template<class T>
inline void LinkBinaryTree<T>::PostOrderTraverse(EleNode * curNode, void(*eNodeFuntion)(EleNode *eNode))
{
	if (curNode != nullptr) {
		PostOrderTraverse(curNode->left, eNodeFuntion);
		PostOrderTraverse(curNode->right,eNodeFuntion);
		eNodeFuntion(curNode);
	}
}

template<class T>
inline void LinkBinaryTree<T>::InOrderTraverse(EleNode * curNode, void(*eNodeFuntion)(EleNode *eNode))
{
	if (curNude != nullptr) {
		InOrderTraverse(curNode->left,eNodeFuntion);
		eNodeFuntion(curNode);
		InOrderTraverse(curNode->right, eNodeFuntion);
	}
}

template<class T>
inline void LinkBinaryTree<T>::PreOrderTraverse(EleNode * curNode, void(*eNodeFuntion)(EleNode *eNode))
{
	if (curNude != nullptr) {
		eNodeFuntion(curNode);
		PreOrderTraverse(curNode->left, eNodeFuntion);		
		PreOrderTraverse(curNode->right, eNodeFuntion);
	}
}

template<class T>
inline void LinkBinaryTree<T>::InOrderTraverseWithStack(EleNode * curNude, void(*fun)(T eValue))
{
	EleNode* cur = curNude;//��ǰѭ������Ľڵ�
	stack<LinkBinaryTree<T>::EleNode*>* eNodeStack = new stack<LinkBinaryTree<T>::EleNode*>();//����ڵ��ջ
	stack<char>* haveDir = new stack<char>();//����ڵ���ջ���ݵ�ջ
	haveDir->push('n');
	while (true)
	{
		if (haveDir->empty()) {
			cerr << "Error������ı���������\n" << endl;
		}
		char now = 'f';
		now=haveDir->top();
		haveDir->pop();
		if (now == 'n') {//���Ҿ�δ������ �Ľڵ�
			if (cur->left) {//����ڵ� �ýڵ���ջ��
				eNodeStack->push(cur);
				haveDir->push('l');//ѹ���Ӧ����ջ���� 'l'����ڵ��ѱ�����
				cur = cur->left;
				haveDir->push('n');//�滻��ǰ����ڵ㣬ѹ�� 'n'�����Ҿ�Ϊ���� ������һ��ѭ��
				continue;
			}
			else if (cur->right) {//����ڵ㣬���ҽڵ�
				fun(cur->eleValue); //���ʸýڵ� ������ǰ����ڵ��滻Ϊ�ýڵ���ҽڵ� ѹ��'n' ������һ��ѭ��
				cur = cur->right;
				haveDir->push('n');
				continue;
			}
			else//���ҽڵ���� ����Ҷ��� ����ջ�нڵ���ΪΪ��ǰ����ڵ� ��ջ���޽ڵ����������
			{
				fun(cur->eleValue);				
				if(eNodeStack->empty()){
					delete eNodeStack;
					delete haveDir;
					return;
				}
				cur = eNodeStack->top();
				eNodeStack->pop();
				continue;
			}
		}
		else if (now == 'l') {//�ýڵ�����ѱ���
			if (cur->right) { //���ʸýڵ㲢����ǰ����ڵ��滻Ϊ�ýڵ���ҽڵ� 
				fun(cur->eleValue);
				cur = cur->right;
				haveDir->push('n');
				continue;
			}
			else// ������ڵ� ���ʸýڵ� ����ջ�нڵ�
			{
				fun(cur->eleValue);
				if (eNodeStack->empty()) {
					delete eNodeStack;
					delete haveDir;
					return;
				}
				cur = eNodeStack->top();
				eNodeStack->pop();
				continue;
			}
		}
	}
}






