#pragma once
#include "stdafx.h"

#include <math.h>

using namespace std;

template<class T>
class SqBinaryTree
{
private:
	T * eleArry;//元素储存堆数组指针
	int deep;//深度
	int eleNum;//最大拥有元素数量
	TreeEleType eleType;
public:
	//构造---------------------------------------------------------
	SqBinaryTree(int treeDeep,TreeEleType etype); //默认构造函数
	~SqBinaryTree();
	void clearBinaryTree(bool isfreeptr);
	//清空所有枝叶元素 若是非指针则清空为-1 若是指针（必选指向堆内存）清空为nullptr 并释放指针指向的内存
	void clearBinaryTree();

	void LevelOrderTraverse(void(*fun)(T ele));

	void addEleTo(const char* pos, T newEle, bool isReplace);//char* 引导序列 bool 是否在已有元素时强制替换
	void removeEleAt(const char* pos);
	
};

template<class T>
inline SqBinaryTree<T>::SqBinaryTree(int treeDeep, TreeEleType etype)
{
	//计算元素数量
	eleNum = 0;
	for (int i = 0; i < treeDeep; i++) {
		eleNum += (int)pow(2, i);
	}
	if (eleNum <= 0) {
		cout << "\n错误的深度！！！\n" << endl;
		return;
	}
	
	//构造储存堆数组，初始化
	deep = treeDeep;
	eleArry = (T*)malloc(sizeof(T)*(eleNum + 1));
	eleType = etype;

	if (eleArry) {
		cout << "\n顺序储存二叉树成功构造\n深度：" << treeDeep << "\n最大元素数量：" << eleNum << endl;
	}
	else
	{
		cerr << "\nError：无法获取足够的堆空间！！！\n" << endl;
	}

}

template<class T>
inline SqBinaryTree<T>::~SqBinaryTree()
{
	if (eleType == TreeEleType::Ptr) {
		clearBinaryTree(true);
	}
}

template<class T>
inline void SqBinaryTree<T>::clearBinaryTree(bool isfreeptr)
{
	if (eleType == TreeEleType::Num) { //数据元素，清空为-1
		for (int i =0; i <= eleNum; i++) {
			eleArry[i] = (T)-1;//请放心，我们区分了指针与非指针
		}

	}
	else
	{
		for (int i = 0; i <= eleNum; i++) {
			if (isfreeptr&&eleArry[i]) {
				free((void*)eleArry[i]);
			}
			eleArry[i] =(T)nullptr;
		}
	}
	cout << "\n完成顺序储存二叉树清空\n" << endl;
}

template<class T>
inline void SqBinaryTree<T>::clearBinaryTree()
{
	if (eleType == TreeEleType::Num) { //数据元素，清空为-1
		for (int i = 0; i <= eleNum; i++) {
			eleArry[i] = (T)-1; 
		}

	}
	else
	{
		cerr << "\n错误的调用！！！请调用 void SqBinaryTree<T>::clearBinaryTree(bool isfreeptr)\n" << endl;
		return;
	}
	cout << "完成顺序储存二叉树清空" << endl;
}

template<class T>
inline void SqBinaryTree<T>::LevelOrderTraverse(void(*fun)(T ele))
{
	cout << "\n开始层序访问:\n" << endl;
	int flag = 1;
	if (eleType == TreeEleType::Num) {
		for (int i = 0; i < deep; i++) {
			for (int j = 0; j < (int)pow(2, i); j++) {
				cout << "第" << i+1 << "层(" << j+1 <<")："<<endl;
				if (eleArry[flag] != (T)-1) {
					fun(eleArry[flag]);
				}
				flag++;
			}
			cout << "\n" << endl;
		}
	}
	else
	{
		for (int i = 0; i < deep; i++) {
			for (int j = 0; j < (int)pow(2, i); j++) {
				cout << "第" << i << "层：" << endl;
				if (eleArry[flag] != (T)nullptr) {
					fun(eleArry[flag]);
				}
				flag++;
			}
		}
	}
}

template<class T>
inline void SqBinaryTree<T>::addEleTo(const char * pos,T newEle ,bool isReplace)
{

	if (pos[0] != '0') {
		cerr << "\n错误的引导序列！！！" << endl;
		return;
	}

	int flag = 1;
	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (pos[i] == '0') {
			flag = flag * 2;
		}
		else if (pos[i] == '1') {
			flag = flag * 2 + 1;
		}
		else
		{
			cerr << "\n错误的引导序列！！！" << endl;
			return;
		}
	}
	if (flag > eleNum) {
		cerr << "\n错误的引导序列！！！" << endl;
		return;
	}


	if (eleType == TreeEleType::Num) {
		if (eleArry[flag] == (T)-1) {
			eleArry[flag] = newEle;
			cout << "\n插入成功！！！" << endl;
		}
		else if(isReplace)
		{
			eleArry[flag] = newEle;
			cout << "\n元素已存在，强制替换！！！" << endl;
		}
		else
		{
			cout << "\n插入失败！！！" << endl;
		}
	}
	else
	{
		if (eleArry[flag] == (T)nullptr) {
			eleArry[flag] = newEle;
			cout << "\n插入成功！！！" << endl;
		}
		else if (isReplace)
		{
			free((void*)eleArry[flag]);
			eleArry[flag] = newEle;
			cout << "\n元素已存在，强制替换！！！" << endl;
		}
		else
		{
			cout << "\n插入失败！！！" << endl;
		}
	}
}

template<class T>
inline void SqBinaryTree<T>::removeEleAt(const char * pos)
{
	if (pos[0] != '0') {
		cerr << "\n错误的引导序列！！！" << endl;
		return;
	}

	int flag = 1;
	for (int i = 1; pos[i] != '\0'&&pos[i] != '\n'; i++) {
		if (pos[i] == '0') {
			flag = flag * 2;
		}
		else if (pos[i] == '1') {
			flag = flag * 2 + 1;
		}
		else
		{
			cerr << "\n错误的引导序列！！！" << endl;
			return;
		}
	}
	if (flag > eleNum) {
		cerr << "\n错误的引导序列！！！" << endl;
		return;
	}


	if (eleType == TreeEleType::Num) {
		if (eleArry[flag] != (T)-1) {
			eleArry[flag] = (T)-1;
			cout << "\n成功清楚！！！" << endl;
		}
		else
		{
			cout << "\n该位置没有元素！！！" << endl;
		}
	}
	else
	{
		if (eleArry[flag] != (T)nullptr) {
			free((void*)eleArry[flag]);
			eleArry[flag] =(T) nullptr;
			cout << "\n成功清楚！！！" << endl;
		}
		else
		{
			cout << "\n该位置没有元素！！！" << endl;
		}
	}
}







//typedef char TElemType;     // 假设二叉树结点的元素类型为字符
//
//// 顺序存储的二叉树结构体
//typedef struct {
//   TElemType *elem;     // 0号单元闲置
//   int lastIndex;              // 二叉树最后一个结点的编号
//} SqBiTree;    // 顺序存储的二叉树
//
//typedef struct  BiTNode {
//    TElemType      data;     // 数据域
//    struct BiTNode  *lchild,*rchild;  // 左、右孩子指针
//} BiTNode,*BiTree;   // 二叉链表
//
//enum Status{
//	SUCEESS,
//	ERROR
//};
//
//
//Status InitBiTree(BiTree T);
////操作结果：构造空二叉树T
//Status DestroyBiTree(BiTree T);
////初始条件：二叉树T存在
////操作结果：摧毁二叉树T
//Status CreateBiTree(BiTree T, char* definition);
////初始条件： definition给出二叉树的定义
////操作结果：按definition构造二叉树T
//
//
////以下部分函数定义未指定参数类型
//Status PreOrderTraverse(BiTNode T, Status (*visit)(TElemType e));
////初始条件：二叉树T存在，visit为对结点的操作的应用函数
////操作结果：先序遍历T，对每个结点调用visit函数一次且仅一次，一旦visit失败，则操作失败
//Status InOrderTraverse(BiTNode T, Status (*visit)(TElemType e));	//中序遍历
//Status PostOrderTraverse(BiTNode T, Status (*visit)(TElemType e)));	//后序遍历
//Status LevelOrderTraverse(BiTNode T, Status (*visit)(TElemType e));	//层序遍历
//int Value(BiTNode T);			//构造出的二叉树求值
///*
//提示：可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
//可根据需要自行增加操作.
//*/


