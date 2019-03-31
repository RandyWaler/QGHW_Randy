#pragma once
enum SymbolType
{
	Number,//����
	Operator//�����
};

struct Symbol
{
	SymbolType type;
	char ch;
	float fl;
};

namespace symbolEle {
	typedef Symbol ElemType;
	struct Node {
		ElemType data;//Ԫ������
		struct Node *next;//��һ��Ԫ��ָ��
	};
}
class ForwardList {//��������



protected:

	symbolEle::Node * head;//����ͷ
	symbolEle::Node* tail;//����β

	

	int listSize = 0;
public:

	static symbolEle::Node* getNewNode();//����һ���´�����Node

	/*
	* ��ʼ������
	*/
	ForwardList();

	/*
	* ��������
	*/
	~ForwardList();

	/*
	* ���������е�һ��Ԫ�ص�����
	*/
	symbolEle::ElemType* front();

	/*
	* �������������һ��Ԫ�ص�����
	*/
	symbolEle::ElemType* back();


	/*
	* �������һ��Ԫ��ǰ���Ԫ��e
	*/
	bool push_front(symbolEle::ElemType& e);

	/*
	* ɾ�������һ��Ԫ��
	*/
	bool pop_front();

	/*
	* ���������һ��Ԫ�غ����Ԫ��e
	*/
	bool push_back(symbolEle::ElemType& e);

	/*
	* ɾ���������һ��Ԫ��
	*/
	bool pop_back();

	/*
	* �������
	*/
	bool clear();

	/*
	* ����������Ԫ�ص�����
	*/
	unsigned int size();

	/*
	* ��������, ��ÿ��Ԫ�ص���visitָ��ĺ���
	*/
	bool traverse(void(*visit)(symbolEle::ElemType& e));

	/*
	* չʾ����Ԫ�� �������չʾ
	*/
	void showAllEle();
	/*
	*չʾ����Ԫ�� �ո���չʾ
	*/
	void showAllEleLink();

	/*
	*��õڶ���Ԫ��
	*/
	void getSceondEle(symbolEle::ElemType* ele);//��Ը��Ŵ���
	/*
	*��õ�n��Ԫ��
    */
	void getNEle(symbolEle::ElemType* ele,int n);//��Ը��Ŵ���
};



