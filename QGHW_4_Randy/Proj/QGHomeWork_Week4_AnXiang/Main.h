#pragma once

#define oW 10000
#define fW 50000
#define twW 200000

int* rArry1w;
int* rArry5w;
int* rArry20w;

int tryGetNum(const char *str);//���Զ�ȡһ������ ���������ַ�����ʾ��������
int tryGetNum(const char *str, int min, int max);
int tryGetNum(const char *str, int min);

int* getRandArry(int length);//��������Ķѿռ䣬�������ֵ
bool setRandArry();//��ʼ���������
void reSetRandArry();//�����������ռ�

void checkArry(int*arry, int length);//���������
void icheckArry(int*arry, int length);

bool getCode();