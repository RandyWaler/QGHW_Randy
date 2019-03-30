#pragma once
#include <iostream>
#include <malloc.h>

using namespace std;

template<class T>
class SqStack
{
private:
	T * top=nullptr;
	int sizeNow = 0;//当前大小
	int sizeMax = 0;//最大大小
	T *elem=nullptr;
	bool isClear = true;//是否被清空
public:
	//初始化-------------------------------
	SqStack(int Size);
	~SqStack();
	bool initStack(int Size);//初始化方法
    //栈相关
	int getSizeNow();//获得栈的当前大小
	int getSizeMax();//获得栈的最大容量
	bool isStackEmpty();//判断是否为空栈
	T* getStackTopEle();//获得栈顶元素指针
	bool clearStack();//清空栈
	bool pushStack(T ele);//入栈
	bool popStack(T* pop);//出栈
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
bool SqStack<T>::initStack(int Size)//初始化方法
{
	if (elem) {//若不为空，先清楚栈指针已有的堆空间
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
int SqStack<T>::getSizeNow()//获得当前大小
{
	return sizeNow;
}

template<class T>
int SqStack<T>::getSizeMax()//获得最大大小
{
	return sizeMax;
}

template<class T>
bool SqStack<T>::isStackEmpty()//是否为空栈
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



