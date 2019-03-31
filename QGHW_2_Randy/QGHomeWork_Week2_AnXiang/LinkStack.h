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
	int sizeNow = 0;//��ǰ��С
	bool isClear = true;//�Ƿ����
	
public:
	LinkEle* head=nullptr;
	LinkEle* tail=nullptr;
	LinkStack();
	~LinkStack();
	bool initStack();//��ʼ������

	LinkEle* getNewLinkEle() {
		LinkEle* newEle = (LinkEle*)malloc(sizeof(LinkEle));
		if (newEle) {
			//newEle->eleValue = NULL;
			newEle->next = nullptr;
			return newEle;
		}
		return nullptr;
	}

	//ջ���------------------------------------------------
	int getSizeNow();//���ջ�ĵ�ǰ��С
	bool isStackEmpty();//�ж��Ƿ�Ϊ��ջ
	ElemType* getStackTopEle();//���ջ��Ԫ��ָ��
	bool clearStack();//���ջ
	bool pushStack(T ele);//��ջ
	bool popStack(T* pop);//��ջ

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
		cout << "pushδ��ʼ����ջ������" << endl;
		return false;
	}
	if (tail == head) { //ջ����Ԫ��
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
		cout << "popδ��ʼ����ջ������" << endl;
		return false;
	}
	if (tail == head) {//ջ����Ԫ��
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
