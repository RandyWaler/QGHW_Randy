#pragma once
#include "stdafx.h"

#include"Symbol.h"

#include <stack>

using namespace std;
using namespace symbolEle;

template<class T>
class LinkBinaryTree {
public:
	//节点
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
		cerr << "Error：无法获取堆空间！！！\n" << endl;
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
			cerr << "\nError：错误的引导序列！！！\n" << endl;
			return nullptr;
		}
		EleNode* cur = root;

		for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
			if (!cur) {
				cerr << "\nError：错误的引导序列！！！\n" << endl;
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
				cerr << "\nError：错误的引导序列！！！奇异符号\n" << endl;
				return nullptr;
			}
		}
		return cur;
	}

	T getValueAt(const char* pos);

	bool addEleTo(const char* pos, T ele, bool isReplace);
	
	bool removeEleAt(const char* pos,bool isBreak);//char* pos引导序列 bool isBreak是否强制截枝 

	void removeFrmoNode(EleNode* sNode,bool issaveStart);//从某个起始节点开始删除 是否保留起始点


	void ClearTree();

	TreeEleType getTreeEleType();

	//void seteNodeFuntion(void(*fun)(EleNode* eNode));
	
	static void doThisFun(LinkBinaryTree<T>* tree,EleNode * eNode, const char * doFun);

//递归实现---------------------------------------------------------------------------------------------------------
	static void PreOrderTraverse(EleNode* curNude, void(*fun)(T eValue));//对每个值的访问
	static void InOrderTraverse(EleNode* curNude, void(*fun)(T eValue));
	static void PostOrderTraverse(EleNode* curNude, void(*fun)(T eValue));

	static void PreOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);//对每个节点的访问
	static void InOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);
	static void PostOrderTraverse(LinkBinaryTree<T>* tree, EleNode* curNude, const char* doFun);

	static void PostOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
	static void InOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
	static void PreOrderTraverse(EleNode* curNode, void(*eNodeFuntion)(EleNode* eNode));
//非递归实现-------------------------------------------------------------------------------------------------------
	static void InOrderTraverseWithStack(EleNode* curNude, void(*fun)(T eValue));
};

template<class T>
inline LinkBinaryTree<T>::LinkBinaryTree(TreeEleType type)
{
	eleType = type;
	if (eleType == TreeEleType::Num) {
		root = getNewEleNode((T)INT_MIN);
		if (!root) {
			cerr << "\nError：无法获取堆空间\n" << endl;
			return;
		}
	}
	else
	{
		root = getNewEleNode((T)nullptr);
		if (!root) {
			cerr << "\nError：无法获取堆空间\n" << endl;
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
		cerr << "\nError：错误的引导序列！！！\n" << endl;
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
			cerr << "\nError：错误的引导序列！！！\n" << endl;
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
			cerr << "\nError：错误的引导序列！！！奇异符号\n" << endl;
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
		cerr << "\nError：错误的引导序列！！！\n" << endl;
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
		cerr << "\nError：错误的引导序列！！！\n" << endl;
		return false;
	}
	EleNode* cur = root;
	EleNode** pre;

	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (!cur) {
			cerr << "\nError：错误的引导序列！！！\n" << endl;
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
			cerr << "\nError：错误的引导序列！！！奇异符号\n" << endl;
			return false;
		}
	}
	if (cur == root) {//根节点插入
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
				cout << "\nError：根节点插入，元素已存在权限不足！！！\n" << endl;
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
				cout << "\nError：根节点插入，元素已存在权限不足！！！\n" << endl;
				return false;
			}
		}
	}else {
		if (!cur) {//该位置是一个空节点
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
			cerr << "Error：该位置已有节点，权限不足！！！" << endl;
			return false;
		}
	}

}

template<class T>
inline bool LinkBinaryTree<T>::removeEleAt(const char * pos, bool isBreak)
{
	if (pos[0] != '0') {
		cerr << "\n错误的引导序列！！！\n" << endl;
		return false;
	}
	EleNode* cur = root;//要删除的节点
	EleNode** pre;//指向cur的指针的指针
	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (!cur) {
			cerr << "\n错误的引导序列！！！指向空节点，无法继续索引\n" << endl;
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
			cerr << "\n错误的引导序列！！！异常字符\n" << endl;
			return false;
		}
	}
	if (cur == root) {
		cerr << "\n错误的引导序列！！！不可删除根节点" << endl;
		return false;
	}
	if (!cur) {
		cerr << "\n该位置没有元素！！！" << endl;
		return true;
	}

    if (isBreak) {//强制截枝
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
		cerr << "\n错误的引导序列！！！不可删除有还有枝叶的节点，请更改权限" << endl;
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
	EleNode* cur = curNude;//当前循环处理的节点
	stack<LinkBinaryTree<T>::EleNode*>* eNodeStack = new stack<LinkBinaryTree<T>::EleNode*>();//保存节点的栈
	stack<char>* haveDir = new stack<char>();//保存节点入栈数据的栈
	haveDir->push('n');
	while (true)
	{
		if (haveDir->empty()) {
			cerr << "Error：错误的遍历！！！\n" << endl;
		}
		char now = 'f';
		now=haveDir->top();
		haveDir->pop();
		if (now == 'n') {//左右均未被遍历 的节点
			if (cur->left) {//有左节点 该节点入栈，
				eNodeStack->push(cur);
				haveDir->push('l');//压入对应的入栈数据 'l'：左节点已被遍历
				cur = cur->left;
				haveDir->push('n');//替换当前处理节点，压入 'n'：左右均为遍历 开启下一次循环
				continue;
			}
			else if (cur->right) {//无左节点，有右节点
				fun(cur->eleValue); //访问该节点 并将当前处理节点替换为该节点的右节点 压入'n' 开启下一次循环
				cur = cur->right;
				haveDir->push('n');
				continue;
			}
			else//左右节点均无 访问叶结点 弹出栈中节点设为为当前处理节点 若栈中无节点则遍历结束
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
		else if (now == 'l') {//该节点的左已遍历
			if (cur->right) { //访问该节点并讲当前处理节点替换为该节点的右节点 
				fun(cur->eleValue);
				cur = cur->right;
				haveDir->push('n');
				continue;
			}
			else// 若无左节点 访问该节点 弹出栈中节点
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






