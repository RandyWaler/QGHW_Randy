#include <iostream>
#include <malloc.h>

using namespace std;

template<class T>
class LinkStack
{
public:
	typedef T ElemType;
	struct LinkEle
	{
		ElemType eleValue;
		LinkEle* next;
	};
private:
	T * top = nullptr;
	int sizeNow = 0;//当前大小
	bool isClear = true;//是否被清空
	
public:
	LinkEle* head=nullptr;
	LinkEle* tail=nullptr;
	LinkStack();
	~LinkStack();
	bool initStack();//初始化方法

	LinkEle* getNewLinkEle() {
		LinkEle* newEle = (LinkEle*)malloc(sizeof(LinkEle));
		if (newEle) {
			//newEle->eleValue = NULL;
			newEle->next = nullptr;
			return newEle;
		}
		return nullptr;
	}

	//栈相关------------------------------------------------
	int getSizeNow();//获得栈的当前大小
	bool isStackEmpty();//判断是否为空栈
	ElemType* getStackTopEle();//获得栈顶元素指针
	bool clearStack();//清空栈
	bool pushStack(T ele);//入栈
	bool popStack(T* pop);//出栈

};


template<class T>
inline LinkStack<T>::LinkStack()
{
	initStack();
}

template<class T>
inline LinkStack<T>::~LinkStack()
{
	clearStack();
}

template<class T>
inline bool LinkStack<T>::initStack()
{
	if (head) {
		isClear = false;
		clearStack();
		return true;
	}
	else
	{
		head = getNewLinkEle();
		if (!head) {
			return false;
		}
		tail = head;
		isClear = false;
		sizeNow = 0;
		top = nullptr;

		return true;
	}
}

template<class T>
inline int LinkStack<T>::getSizeNow()
{
	return sizeNow;
}

template<class T>
inline bool LinkStack<T>::isStackEmpty()
{
	return (tail==head);
}

template<class T>
inline T * LinkStack<T>::getStackTopEle()
{
	return top;
}

template<class T>
inline bool LinkStack<T>::clearStack()
{
	if (tail == head) {
		return false;
	}
	if (isClear) {
		return false;
	}
	LinkStack::LinkEle* curEle = head->next;
	LinkStack::LinkEle* preEle=curEle;
	while (sizeNow)
	{
		curEle = curEle->next;
		free(preEle);
		preEle = curEle;
		sizeNow--;
	}


	tail = head;
	isClear = true;
	sizeNow = 0;
	top = nullptr;

	return true;
}

template<class T>
inline bool LinkStack<T>::pushStack(T ele)
{
	if (isClear) {
		cout << "push未初始化的栈！！！" << endl;
		return false;
	}
	if (tail == head) { //栈中无元素
		LinkStack::LinkEle* newEle = getNewLinkEle();
		if (!newEle) {
			return false;
		}
		newEle->eleValue = ele;
		head->next = newEle;
		tail = newEle;
		sizeNow=1;
		top = &newEle->eleValue;
		return true;
	}
	else
	{
		LinkStack::LinkEle* newEle = getNewLinkEle();
		if (!newEle) {
			return false;
		}
		newEle->eleValue = ele;
		sizeNow++;
		top = &newEle->eleValue;
		tail->next = newEle;
		tail = newEle;
		return true;
	}
}

template<class T>
inline bool LinkStack<T>::popStack(T * pop)
{
	
	if (isClear) {
		cout << "pop未初始化的栈！！！" << endl;
		return false;
	}
	if (tail == head) {//栈中无元素
		return false;
	}
	if (tail == head->next) {
		*pop = tail->eleValue;
		free(tail);
		tail = head;
		sizeNow=0;
		top = nullptr;
		return true;
	}
	else
	{
		*pop = tail->eleValue;
		LinkStack::LinkEle* cur = head->next;
		while (tail != cur->next)
		{
			cur = cur->next;
		}
		free(tail);
		tail = cur;
		sizeNow--;
		top = &tail->eleValue;
		return true;
	}
}
