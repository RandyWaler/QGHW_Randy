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
	//����ͷ����
	head = ForwardList::getNewNode();
	//malloc ����Ϊ��
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
	//ѭ��ɾ��
	Node* node = head->next;
	Node* node2 = node;
	while (node)
	{
		node = node->next;
		free(node2);
		node2 = node;
	}
	//��ʼ������ͷβ������
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
	//����
	Node* newNode = ForwardList::getNewNode();
	//malloc ����Ϊ��
	if (NULL == newNode) {
		logMallocError();
		return false;
	}
	newNode->data = e;
	//����
	newNode->next = head->next;
	head->next = newNode;

	listSize++;
	//��ʱ��ΨһԪ�ز��룬����βԪ��Ϊ�²����Ԫ��
	if (tail == head) {
		tail = newNode;
	}
	return true;
	
}

bool ForwardList::pop_front()
{
	if (tail == head) {//û�е�һ��Ԫ��
		return false;
	}
	if (head->next == tail) {//ֻ��һ��Ԫ��ʱ
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
	if (tail == head) {//û�����һ��Ԫ��
		return push_front(e);//������ǰ��ӵ��������
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
		return false;//û�����һ��Ԫ��
	}
	if (head->next == tail) {//ֻ��һ��Ԫ��ʱ
		free(tail);
		tail = head;
		head->next = NULL;
		listSize = 0;
		return true;
	}
	//��ֹһ��Ԫ��ʱ
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
	//ѭ��ɾ��
	Node* node = head->next;
	Node* node2 = node;
	while (node)
	{
		node = node->next;
		free(node2);
		node2 = node;
	}
	//��ʼ������ͷβ������
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
		cout << "���ʽΪ��" << endl;
		return;
	}
	Node* cur = head->next;
	while (cur)
	{
		if (cur->data.type == SymbolType::Number) {
			cout << "���֣�" << cur->data.fl << endl;
		}
		else
		{
			cout << "�����" << cur->data.ch << endl;
		}
		cur = cur->next;
	}
	cout << "\n" << endl;
}

void ForwardList::showAllEleLink()
{
	if (tail == head) {
		cout << "���ʽΪ��" << endl;
		return;
	}
	cout << "���ʽΪ��" << endl;
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
