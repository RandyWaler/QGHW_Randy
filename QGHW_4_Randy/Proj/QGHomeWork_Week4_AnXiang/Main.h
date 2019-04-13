#pragma once

#define oW 10000
#define fW 50000
#define twW 200000

int* rArry1w;
int* rArry5w;
int* rArry20w;

int tryGetNum(const char *str);//尝试读取一个数字 若有其他字符，提示重新输入
int tryGetNum(const char *str, int min, int max);
int tryGetNum(const char *str, int min);

int* getRandArry(int length);//申请数组的堆空间，并赋随机值
bool setRandArry();//初始化随机数组
void reSetRandArry();//回收随机数组空间

void checkArry(int*arry, int length);//检查排序结果
void icheckArry(int*arry, int length);

bool getCode();