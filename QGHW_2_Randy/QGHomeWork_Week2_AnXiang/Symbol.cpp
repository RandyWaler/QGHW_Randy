#include "Symbol.h"

#include <iostream>
#include <malloc.h>

using namespace std;
using namespace symbolEle;

void logMallocError() {
	cout << "\nmalloc NULL!!!" << endl;
}


Node * ForwardList::getNewNode()
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode) {
		newNode->data = {SymbolType::Number,'\0',0.0f};
		newNode->next = NULL;
		return newNode;
	}
	return NULL;
}

ForwardList::ForwardList()
{
	//创建头链表
	head = ForwardList::getNewNode();
	//malloc 返回为空
	if (NULL == head) {
		logMallocError();
		cout << "Fail Init!!!" << endl;
		return;
	}
	listSize = 0;
	tail = head;
}

ForwardList::~ForwardList()
{
	//循环删除
	Node* node = head->next;
	Node* node2 = node;
	while (node)
	{
		node = node->next;
		free(node2);
		node2 = node;
	}
	//初始化链表头尾及数据
	head->next = NULL;
	tail = head;
	listSize = 0;
}

ElemType * ForwardList::front()
{
	if (head->next) {
		return &(head->next->data);
	}
	return NULL;
}

ElemType * ForwardList::back()
{
	if (tail != head) {
		return  &(tail->data);
	}
	return NULL;
}

bool ForwardList::push_front(symbolEle::ElemType & e)
{
	//创建
	Node* newNode = ForwardList::getNewNode();
	//malloc 返回为空
	if (NULL == newNode) {
		logMallocError();
		return false;
	}
	newNode->data = e;
	//插入
	newNode->next = head->next;
	head->next = newNode;

	listSize++;
	//此时是唯一元素插入，设置尾元素为新插入的元素
	if (tail == head) {
		tail = newNode;
	}
	return true;
	
}

bool ForwardList::pop_front()
{
	if (tail == head) {//没有第一个元素
		return false;
	}
	if (head->next == tail) {//只有一个元素时
		free(tail);
		tail = head;
		head->next = NULL;
		listSize = 0;
		return true;
	}
	Node* newFirs = head->next->next;
	free(head->next);
	head->next = newFirs;

	listSize--;
	return true;
}

bool ForwardList::push_back(symbolEle::ElemType & e)
{
	if (tail == head) {//没有最后一个元素
		return push_front(e);//按向最前添加的情况处理
	}
	Node* newNode = ForwardList::getNewNode();
	if (NULL == newNode) {
		logMallocError();
		return false;
	}
	newNode->data = e;
	tail->next = newNode;
	tail = newNode;

	listSize++;
	return true;
}

bool ForwardList::pop_back()
{
	if (tail == head) {
		return false;//没有最后一个元素
	}
	if (head->next == tail) {//只有一个元素时
		free(tail);
		tail = head;
		head->next = NULL;
		listSize = 0;
		return true;
	}
	//不止一个元素时
	Node* cur = head->next;
	while (cur->next != tail)
	{
		cur = cur->next;
	}
	cur->next = NULL;
	free(tail);
	tail = cur;


	listSize--;
	return true;
}

bool ForwardList::clear()
{
	if (tail == head) {
		return false;
	}
	//循环删除
	Node* node = head->next;
	Node* node2 = node;
	while (node)
	{
		node = node->next;
		free(node2);
		node2 = node;
	}
	//初始化链表头尾及数据
	head->next = NULL;
	listSize = 0;
	tail = head;
	return true;
}

unsigned int ForwardList::size()
{
	return listSize;
}

bool ForwardList::traverse(void(*visit)(symbolEle::ElemType &e))
{
	if (tail == head) {
		return false;
	}
	Node* cur = head->next;
	while (cur)
	{
		visit(cur->data);
		cur = cur->next;
	}
	return true;
}

void ForwardList::showAllEle()
{
	if (tail == head) {
		cout << "表达式为空" << endl;
		return;
	}
	Node* cur = head->next;
	while (cur)
	{
		if (cur->data.type == SymbolType::Number) {
			cout << "数字：" << cur->data.fl << endl;
		}
		else
		{
			cout << "算符：" << cur->data.ch << endl;
		}
		cur = cur->next;
	}
	cout << "\n" << endl;
}

void ForwardList::showAllEleLink()
{
	if (tail == head) {
		cout << "表达式为空" << endl;
		return;
	}
	cout << "表达式为：" << endl;
	Node* cur = head->next;
	while (cur)
	{
		if (cur->data.type == SymbolType::Number) {
			cout << cur->data.fl<<" ";
		}
		else
		{
			cout <<cur->data.ch <<" ";
		}
		cur = cur->next;
	}
	cout << "\n" << endl;
}

void ForwardList::getSceondEle(symbolEle::ElemType * ele)
{
	if (tail == head) {
	
		ele = nullptr;
		return;
	}
	else if(listSize<2)
	{
	
		ele = nullptr;
		return;
	}

	*ele = head->next->next->data;

}
