
#ifndef AQUEUE_H_INCLUDED
#define AQUEUE_H_INCLUDED

#include "State.h"
#include <stdio.h>
#include <malloc.h>
/**************************************************************
 *    Struct Define Section
 **************************************************************/
//链式队列结构
typedef struct node
{
    void *data;                   //数据域指针
	int die;
    struct node *next;            //指向当前结点的下一结点
} Node;

//die //被void* 吃掉的不是队列的字段 die不是AQueue的成员，它一开始被声明出来就是为了为下面的字段抗这未知的一刀 让我们缅怀这伟大的字段吧
//你无法删除字段die否则next就会被吃掉 你甚至不能在die的那一行写注释 否则也会出错

typedef struct Lqueue
{
    Node *front;                   //队头
    Node *rear;                    //队尾
    size_t length;            //队列长度
	char type[16];
} LQueue;


/**************************************************************
 *    Prototype Declare Section
 **************************************************************/


/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q,const char type[]) {
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
	copyStr(Q->type, type);
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q) {
	Node* n = Q->front;
	Node* n2 = n;
	for (int i = 0; i < Q->length; i++) {
		n = n->next;
		free(n2->data);
		free(n2);
		n2 = n;
	}
	free(Q);
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q) {
	if (Q->length <= 0) {
		return TRUE;
	}
	return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e) {
	if (Q->length <= 0) {
		return FALSE;
	}
	if (comparStr(Q->type, INT)) {

		int *ele = e;
		int *d = Q->front->data;
		*ele = *d;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q) {
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data) {
	if (Q->length == 0) {
		if (comparStr(Q->type, INT)) {
			Node* newNode = (Node*)malloc(sizeof(Node));
			if (!newNode) {
				return FALSE;
			}
			newNode->data = malloc(sizeof(int));
			if (!newNode->data) {
				return FALSE;
			}
			int *ndata = newNode->data;
			int *idata = data;
			*ndata = *idata;
			Q->front = newNode;
			Q->rear = newNode;
			Q->length=1;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if (comparStr(Q->type, INT)) {
			Node* newNode = (Node*)malloc(sizeof(Node));
			if (!newNode) {
				return FALSE;
			}
			newNode->data = malloc(sizeof(int));
			if (!newNode->data) {
				return FALSE;
			}
			int *ndata = newNode->data;
			int *idata = data;
			*ndata = *idata;
			Q->rear->next = newNode;
			Q->rear = newNode;
			Q->length++;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q,void* e) {
	if (IsEmptyLQueue(Q)) {
		return FALSE;
	}

	if (Q->length == 1) {
		if (comparStr(Q->type, INT)) {
			int *ele = e;
			int*dele = Q->front->data;
			*ele = *dele;
			free(Q->front->data);
			free(Q->front);
			Q->length = 0;
			Q->front = NULL;
			Q->rear = NULL;
			return TRUE;

		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if (comparStr(Q->type, INT)) {
			int *ele = e;
			int*dele = Q->front->data;
			*ele = *dele;
			Node* bfree = Q->front;
			Q->front = Q->front->next;
			free(bfree->data);
			free(bfree);
			Q->length--;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q) {
	Node* n = Q->front;
	Node* n2 = n;
	for (int i = 0; i < Q->length; i++) {
		n = n->next;
		free(n2->data);
		free(n2);
		n2 = n;
	}

	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void(*foo)(void *q)) {
	if (IsEmptyLQueue(Q)) {
		return FALSE;
	}

	Node* n = Q->front;
	for (int i = 0; i < Q->length; i++) {
		foo(n->data);
		n = n->next;
	}
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 
 *  @notice      : None
 */
void LPrint(const char str, void *q) {
	if (comparStr(str, INT)) {
		int* p = q;
		printf("%d\n", *p);
	}
}

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/

#endif
