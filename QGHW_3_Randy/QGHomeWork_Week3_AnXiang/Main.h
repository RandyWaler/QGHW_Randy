

#ifndef QGHW_MAIN_H_INCLUDE
#define QGHW_MAIN_H_INCLUDE

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


#include "AQueue.h"
#include "LQueue.h"

//
int tryGetNum(const char str[]);//尝试读取一个数字 若有其他字符，提示重新输入
int tryGetNum2(const char str[], int min, int max);
int tryGetNum3(const char str[], int min);
//
void EnQueue(int a);
void DeQueueAndShow();
void showAllQueue();
void clearQueue();
void isEmptyQueue();
void isFullQueue();
void getHeadEle();
Status getCode();

typedef enum testCase
{
	AQ = 1, LQ = 2
} TestCase;

#endif