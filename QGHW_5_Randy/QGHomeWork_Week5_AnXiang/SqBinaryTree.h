#pragma once
#include "stdafx.h"

#include <math.h>

using namespace std;

template<class T>
class SqBinaryTree
{
private:
	T * eleArry;//Ԫ�ش��������ָ��
	int deep;//���
	int eleNum;//���ӵ��Ԫ������
	TreeEleType eleType;
public:
	//����---------------------------------------------------------
	SqBinaryTree(int treeDeep,TreeEleType etype); //Ĭ�Ϲ��캯��
	~SqBinaryTree();
	void clearBinaryTree(bool isfreeptr);
	//�������֦ҶԪ�� ���Ƿ�ָ�������Ϊ-1 ����ָ�루��ѡָ����ڴ棩���Ϊnullptr ���ͷ�ָ��ָ����ڴ�
	void clearBinaryTree();

	void LevelOrderTraverse(void(*fun)(T ele));

	void addEleTo(const char* pos, T newEle, bool isReplace);//char* �������� bool �Ƿ�������Ԫ��ʱǿ���滻
	void removeEleAt(const char* pos);
	
};

template<class T>
inline SqBinaryTree<T>::SqBinaryTree(int treeDeep, TreeEleType etype)
{
	//����Ԫ������
	eleNum = 0;
	for (int i = 0; i < treeDeep; i++) {
		eleNum += (int)pow(2, i);
	}
	if (eleNum <= 0) {
		cout << "\n�������ȣ�����\n" << endl;
		return;
	}
	
	//���촢������飬��ʼ��
	deep = treeDeep;
	eleArry = (T*)malloc(sizeof(T)*(eleNum + 1));
	eleType = etype;

	if (eleArry) {
		cout << "\n˳�򴢴�������ɹ�����\n��ȣ�" << treeDeep << "\n���Ԫ��������" << eleNum << endl;
	}
	else
	{
		cerr << "\nError���޷���ȡ�㹻�Ķѿռ䣡����\n" << endl;
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
	if (eleType == TreeEleType::Num) { //����Ԫ�أ����Ϊ-1
		for (int i =0; i <= eleNum; i++) {
			eleArry[i] = (T)-1;//����ģ�����������ָ�����ָ��
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
	cout << "\n���˳�򴢴���������\n" << endl;
}

template<class T>
inline void SqBinaryTree<T>::clearBinaryTree()
{
	if (eleType == TreeEleType::Num) { //����Ԫ�أ����Ϊ-1
		for (int i = 0; i <= eleNum; i++) {
			eleArry[i] = (T)-1; 
		}

	}
	else
	{
		cerr << "\n����ĵ��ã���������� void SqBinaryTree<T>::clearBinaryTree(bool isfreeptr)\n" << endl;
		return;
	}
	cout << "���˳�򴢴���������" << endl;
}

template<class T>
inline void SqBinaryTree<T>::LevelOrderTraverse(void(*fun)(T ele))
{
	cout << "\n��ʼ�������:\n" << endl;
	int flag = 1;
	if (eleType == TreeEleType::Num) {
		for (int i = 0; i < deep; i++) {
			for (int j = 0; j < (int)pow(2, i); j++) {
				cout << "��" << i+1 << "��(" << j+1 <<")��"<<endl;
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
				cout << "��" << i << "�㣺" << endl;
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
		cerr << "\n������������У�����" << endl;
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
			cerr << "\n������������У�����" << endl;
			return;
		}
	}
	if (flag > eleNum) {
		cerr << "\n������������У�����" << endl;
		return;
	}


	if (eleType == TreeEleType::Num) {
		if (eleArry[flag] == (T)-1) {
			eleArry[flag] = newEle;
			cout << "\n����ɹ�������" << endl;
		}
		else if(isReplace)
		{
			eleArry[flag] = newEle;
			cout << "\nԪ���Ѵ��ڣ�ǿ���滻������" << endl;
		}
		else
		{
			cout << "\n����ʧ�ܣ�����" << endl;
		}
	}
	else
	{
		if (eleArry[flag] == (T)nullptr) {
			eleArry[flag] = newEle;
			cout << "\n����ɹ�������" << endl;
		}
		else if (isReplace)
		{
			free((void*)eleArry[flag]);
			eleArry[flag] = newEle;
			cout << "\nԪ���Ѵ��ڣ�ǿ���滻������" << endl;
		}
		else
		{
			cout << "\n����ʧ�ܣ�����" << endl;
		}
	}
}

template<class T>
inline void SqBinaryTree<T>::removeEleAt(const char * pos)
{
	if (pos[0] != '0') {
		cerr << "\n������������У�����" << endl;
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
			cerr << "\n������������У�����" << endl;
			return;
		}
	}
	if (flag > eleNum) {
		cerr << "\n������������У�����" << endl;
		return;
	}


	if (eleType == TreeEleType::Num) {
		if (eleArry[flag] != (T)-1) {
			eleArry[flag] = (T)-1;
			cout << "\n�ɹ����������" << endl;
		}
		else
		{
			cout << "\n��λ��û��Ԫ�أ�����" << endl;
		}
	}
	else
	{
		if (eleArry[flag] != (T)nullptr) {
			free((void*)eleArry[flag]);
			eleArry[flag] =(T) nullptr;
			cout << "\n�ɹ����������" << endl;
		}
		else
		{
			cout << "\n��λ��û��Ԫ�أ�����" << endl;
		}
	}
}







//typedef char TElemType;     // �������������Ԫ������Ϊ�ַ�
//
//// ˳��洢�Ķ������ṹ��
//typedef struct {
//   TElemType *elem;     // 0�ŵ�Ԫ����
//   int lastIndex;              // ���������һ�����ı��
//} SqBiTree;    // ˳��洢�Ķ�����
//
//typedef struct  BiTNode {
//    TElemType      data;     // ������
//    struct BiTNode  *lchild,*rchild;  // ���Һ���ָ��
//} BiTNode,*BiTree;   // ��������
//
//enum Status{
//	SUCEESS,
//	ERROR
//};
//
//
//Status InitBiTree(BiTree T);
////�������������ն�����T
//Status DestroyBiTree(BiTree T);
////��ʼ������������T����
////����������ݻٶ�����T
//Status CreateBiTree(BiTree T, char* definition);
////��ʼ������ definition�����������Ķ���
////�����������definition���������T
//
//
////���²��ֺ�������δָ����������
//Status PreOrderTraverse(BiTNode T, Status (*visit)(TElemType e));
////��ʼ������������T���ڣ�visitΪ�Խ��Ĳ�����Ӧ�ú���
////����������������T����ÿ��������visit����һ���ҽ�һ�Σ�һ��visitʧ�ܣ������ʧ��
//Status InOrderTraverse(BiTNode T, Status (*visit)(TElemType e));	//�������
//Status PostOrderTraverse(BiTNode T, Status (*visit)(TElemType e)));	//�������
//Status LevelOrderTraverse(BiTNode T, Status (*visit)(TElemType e));	//�������
//int Value(BiTNode T);			//������Ķ�������ֵ
///*
//��ʾ�����ڽ��ṹ�������ø�Tagֵ��־������������������������
//�ɸ�����Ҫ�������Ӳ���.
//*/


