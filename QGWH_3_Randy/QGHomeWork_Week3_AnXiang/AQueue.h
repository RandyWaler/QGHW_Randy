

#ifndef LQUEUE_H_INCLUDED
#define LQUEUE_H_INCLUDED

#include "State.h"
#include <stdio.h>
#include <malloc.h>
#define MAXQUEUE 10

typedef struct Aqueue
{
	void *data;      //数据域
	int die;
	int front;
	int rear;
    size_t length;        //队列长度
	char type[16];

} AQueue;

//die //被void* 吃掉的不是队列的字段 die不是AQueue的成员，它一开始被声明出来就是为了为下面的字段抗这未知的一刀 让我们缅怀这伟大的字段吧
//你无法删除字段否则front就会被吃掉 你甚至不能在die的哪一行写注释 否则也会出错

int getNextPos(int num) {
	if (num + 1 <= MAXQUEUE - 1) {
		return num + 1;
	}
	return 0;
}

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q,const char type[]) {


	Q->front = 0;
	Q->rear = 0;
	Q->length = 0;	
	copyStr(Q->type, type);
	if (comparStr(Q->type, INT)) {
		Q->data = malloc(sizeof(int) * MAXQUEUE);
	}
	else
	{

	}
}


/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q) {
	free(Q->data);
	free(Q);
}



/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q) {
	
	if (Q->length >= MAXQUEUE) {
		return TRUE;
	}
	return FALSE;
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q) {
	if (Q->length <= 0) {
		return TRUE;
	}
	return FALSE;
}



/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void *e) {
	if (Q->length != 0) {
		if (comparStr(Q->type, INT)) {
			int *p = Q->data;
			int *ele = e;
			*ele = p[Q->front];
			return TRUE;
		}
		else
		{
			//printf("未实现的泛型队列！！！\n");
			return FALSE;
		}
	}
	return FALSE;
}



/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q) {

	return Q->length;
}



/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data) {
	if (IsFullAQueue(Q)) {
		printf("队列已满!!!\n");
		return FALSE;
	}
	if (comparStr(Q->type, INT)) {
		int *p = Q->data;
		int *ele = data;
		p[Q->rear] = *ele;
		Q->length++;
		Q->rear = getNextPos(Q->rear);
		return TRUE;
	}
	else
	{
		//printf("未实现的泛型队列!!!\n");
		return FALSE;
	}
}



/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q,void* data) {
	if (IsEmptyAQueue(Q)) {
		//printf("空队列\n");
		return FALSE;
	}
	if (comparStr(Q->type, INT)) {
		int *p = Q->data;
		int *ele = data;
		*ele = p[Q->front];
		Q->length--;
		Q->front = getNextPos(Q->front);
		return TRUE;
	}
	else
	{
		//printf("未实现的泛型队列!!!\n");
		return FALSE;
	}
}



/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q) {
	if (IsEmptyAQueue(Q)) {
		return;
	}
	
	if (comparStr(Q->type,INT)) {
		int *p = Q->data;
		int flag = Q->front;
		for (int i = 0; i < Q->length; i++) {
			p[flag] = 0;
			flag = getNextPos(flag);
		}
		Q->front = 0;
		Q->rear = 0;
		Q->length = 0;
		
	}
	else
	{

	}
}



/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void(*foo)(void *q)) {
	if (IsEmptyAQueue(Q)) {
		return;
	}

	if (comparStr(Q->type, INT)) {
		int *p = Q->data;
		int flag = Q->front;
		for (int i = 0; i < Q->length; i++) {
			foo(&p[flag]);
			flag = getNextPos(flag);
		}
	}
	else
	{

	}
}



/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
void APrint(const char str, void *q) {
	if (comparStr(str, INT)) {
		int* p = q;
		printf("%d\n", *p);
	}
}



#endif

