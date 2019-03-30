#pragma once
#include <iostream>
#include <malloc.h>

using namespace std;

template<class T>
class SqStack
{
private:
	T * top=nullptr;
	int sizeNow = 0;//��ǰ��С
	int sizeMax = 0;//����С
	T *elem=nullptr;
	bool isClear = true;//�Ƿ����
public:
	//��ʼ��-------------------------------
	SqStack(int Size);
	~SqStack();
	bool initStack(int Size);//��ʼ������
    //ջ���
	int getSizeNow();//���ջ�ĵ�ǰ��С
	int getSizeMax();//���ջ���������
	bool isStackEmpty();//�ж��Ƿ�Ϊ��ջ
	T* getStackTopEle();//���ջ��Ԫ��ָ��
	bool clearStack();//���ջ
	bool pushStack(T ele);//��ջ
	bool popStack(T* pop);//��ջ
};
template<class T>
SqStack<T>::SqStack(int Size)
{
	initStack(Size);
}

template<class T>
SqStack<T>::~SqStack()
{
	clearStack();
}

template<class T>
bool SqStack<T>::initStack(int Size)//��ʼ������
{
	if (elem) {//����Ϊ�գ������ջָ�����еĶѿռ�
		free(elem);
	}
	sizeMax = Size;
	sizeNow = 0;
	top = nullptr;
	elem = (T*)malloc(sizeof(T)*sizeMax);
	if (elem) {
		isClear = false;
		return true;
	}
	return false;
}

template<class T>
int SqStack<T>::getSizeNow()//��õ�ǰ��С
{
	return sizeNow;
}

template<class T>
int SqStack<T>::getSizeMax()//�������С
{
	return sizeMax;
}

template<class T>
bool SqStack<T>::isStackEmpty()//�Ƿ�Ϊ��ջ
{
	return !((bool)sizeNow);
}

template<class T>
T * SqStack<T>::getStackTopEle()
{
	return top;
}

template<class T>
bool SqStack<T>::clearStack()
{
	if (!isClear) {
		if (elem) {
			free(elem);
		}
		elem = nullptr;
		sizeMax = 0;
		sizeNow = 0;
		top = nullptr;
		isClear = true;
		return true;
	}
	return false;
}

template<class T>
bool SqStack<T>::pushStack(T  ele)
{
	if (isClear) {
		return false;
	}
	if (sizeNow < sizeMax) {
		elem[sizeNow] = ele;
		top = &elem[sizeNow];
		sizeNow++;

		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool  SqStack<T>::popStack(T* pop)
{
	if (isClear) {
		return false;
	}
	if (sizeNow <= 0) {
		return false;
	}
	*pop = elem[sizeNow - 1];
	elem[sizeNow - 1] = NULL;
	sizeNow--;
	if (sizeNow > 0) {
		top = &elem[sizeNow - 1];
	}
	else
	{
		top = nullptr;
	}
	return true;

}



