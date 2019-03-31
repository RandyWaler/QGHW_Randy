#pragma once
enum SymbolType
{
	Number,//数字
	Operator//运算符
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
		ElemType data;//元素数据
		struct Node *next;//下一个元素指针
	};
}
class ForwardList {//单项链表



protected:

	symbolEle::Node * head;//链表头
	symbolEle::Node* tail;//链表尾

	

	int listSize = 0;
public:

	static symbolEle::Node* getNewNode();//返回一个新创建的Node

	/*
	* 初始化链表
	*/
	ForwardList();

	/*
	* 销毁链表
	*/
	~ForwardList();

	/*
	* 返回链表中第一个元素的引用
	*/
	symbolEle::ElemType* front();

	/*
	* 返回链表中最后一个元素的引用
	*/
	symbolEle::ElemType* back();


	/*
	* 在链表第一个元素前添加元素e
	*/
	bool push_front(symbolEle::ElemType& e);

	/*
	* 删除链表第一个元素
	*/
	bool pop_front();

	/*
	* 在链表最后一个元素后添加元素e
	*/
	bool push_back(symbolEle::ElemType& e);

	/*
	* 删除链表最后一个元素
	*/
	bool pop_back();

	/*
	* 清空链表
	*/
	bool clear();

	/*
	* 返回链表中元素的数量
	*/
	unsigned int size();

	/*
	* 遍历链表, 对每个元素调用visit指向的函数
	*/
	bool traverse(void(*visit)(symbolEle::ElemType& e));

	/*
	* 展示所有元素 逐个负号展示
	*/
	void showAllEle();
	/*
	*展示所有元素 空格间隔展示
	*/
	void showAllEleLink();

	/*
	*获得第二个元素
	*/
	void getSceondEle(symbolEle::ElemType* ele);//针对负号处理
	/*
	*获得第n个元素
    */
	void getNEle(symbolEle::ElemType* ele,int n);//针对负号处理
};



