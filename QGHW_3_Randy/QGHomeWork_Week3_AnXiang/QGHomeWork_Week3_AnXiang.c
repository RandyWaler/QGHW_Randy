// QGHomeWork_Week3_AnXiang.cpp: 定义控制台应用程序的入口点。
//

#include "Main.h"

AQueue *aq;
LQueue *lq;

int testCase;
int main()
{
	aq = (AQueue*)malloc(sizeof(AQueue));
	InitAQueue(aq,"int");

	lq = (LQueue*)malloc(sizeof(LQueue));
	InitLQueue(lq, "int");

	testCase = tryGetNum2("请选则测试类型 1.顺序队列（空间为10） 2.链队列", 1, 2);

	while (getCode());

	printf("\n测试结束\n");
	system("pause");
    return 0;
}

int tryGetNum(const char  ostr[])
{
	int num = 0;
	int flag = FALSE;

	while (1)
	{
		printf("%s\n", ostr);
		char str[16] = { 0 };
		scanf("%s", str);


		for (num = 0, flag = FALSE; str[num] != '\n'&&str[num] != '\0'; num++) {
			if ((str[num] - '0' > 9 || str[num] - '0' <0) && (num != 0 || str[num] != '-')) {
				flag = TRUE;
				break;
			}
		}
		if (str[0] == '-'&&num == 1) {
			flag = TRUE;
		}
		if (flag) {
			printf("\n----错误，请重输！！----\n");
			
			continue;
		}
		int isnagNum = FALSE;
		if (str[0] == '-') {
			isnagNum = TRUE;
		}
		int iNum = 0;
		int bit = 1;
		if (isnagNum) {
			for (int i = num - 1; i > 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
			iNum *= -1;
		}
		else
		{
			for (int i = num - 1; i >= 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
		}
		return iNum;
	}
}

int tryGetNum2(const char  ostr[], int min, int max)
{
	int num = 0;
	int flag = FALSE;

	while (1)
	{
		printf("%s\n", ostr);
		char str[16] = { 0 };
		scanf("%s", str);


		for (num = 0, flag = FALSE; str[num] != '\n'&&str[num] != '\0'; num++) {
			if ((str[num] - '0' > 9 || str[num] - '0' <0) && (num != 0 || str[num] != '-')) {
				flag = TRUE;
				break;
			}
		}
		if (str[0] == '-'&&num == 1) {
			flag = TRUE;
		}
		if (flag) {
			printf("\n----错误，请重输！！----\n");
			continue;
		}
		int isnagNum = FALSE;
		if (str[0] == '-') {
			isnagNum = TRUE;
		}
		int iNum = 0;
		int bit = 1;
		if (isnagNum) {
			for (int i = num - 1; i > 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
			iNum *= -1;
			if (iNum >= min && iNum <= max) {
				return iNum;
			}
		}
		else
		{
			for (int i = num - 1; i >= 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
			if (iNum >= min && iNum <= max) {
				return iNum;
			}
		}
		printf("\n----错误，请重输！！----\n");
	}
}

int tryGetNum3(const char  ostr[], int min)
{
	int num = 0;
	int flag = FALSE;

	while (1)
	{
		printf("%s\n", ostr);
		char str[16] = { 0 };
		scanf("%s", str);


		for (num = 0, flag = FALSE; str[num] != '\n'&&str[num] != '\0'; num++) {
			if ((str[num] - '0' > 9 || str[num] - '0' <0) && (num != 0 || str[num] != '-')) {
				flag = TRUE;
				break;
			}
		}
		if (str[0] == '-'&&num == 1) {
			flag = TRUE;
		}
		if (flag) {
			printf("\n----错误，请重输！！----\n");
			continue;
		}
		int isnagNum = FALSE;
		if (str[0] == '-') {
			isnagNum = TRUE;
		}
		int iNum = 0;
		int bit = 1;
		if (isnagNum) {
			for (int i = num - 1; i > 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
			iNum *= -1;
			if (iNum >= min) {
				return iNum;
			}
		}
		else
		{

			for (int i = num - 1; i >= 0; i--) {
				iNum += (str[i] - '0')*bit;
				bit *= 10;
			}
			if (iNum >= min) {
				return iNum;
			}
		}
		printf("\n----错误，请重输！！----\n");
	}
}

void EnQueue(int b) {
	

	if (testCase == AQ) {
		if (EnAQueue(aq, &b)) {
			printf("\n%d,入队成功\n", b);
		}
		else
		{
			printf("\n%d,入队失败!!!\n", b);
		}
	}
	else
	{
		if (EnLQueue(lq, &b)) {
			printf("\n%d,入队成功\n", b);
		}
		else
		{
			printf("\n%d,入队失败!!!\n", b);
		}
	}
}

void DeQueueAndShow() {

	int b=0;
	if (testCase == AQ) {
		if (DeAQueue(aq, &b)) {
			printf("\n出队成功：%d\n", b);
		}
		else
		{
			printf("\n出队失败!!!\n");
		}
	}
	else
	{
		if (DeLQueue(lq, &b)) {
			printf("\n出队成功：%d\n", b);
		}
		else
		{
			printf("\n出队失败!!!\n");
		}
	}
}

void showAllQueue()
{
	if (testCase == AQ) {
		if (IsEmptyAQueue(aq)) {
			printf("\n空的队列!!!\n");
			return;
		}
		printf("队列中的元素：\n\n");
		if (comparStr(aq->type, INT)) {
			int *p = aq->data;
			int flag = aq->front;
			for (int i = 0; i < aq->length; i++) {
				printf("第%d个元素：%d\n", i+1, p[flag]);
				flag = getNextPos(flag);
			}
		}
		else
		{

		}
	}
	else
	{
		if (IsEmptyLQueue(lq)) {
			printf("\n空的队列!!!\n");
			return;
		}
		printf("队列中的元素：\n\n");
		if (comparStr(lq->type, INT)) {
			Node* curNode = lq->front;
			int * ele;
			for (int i = 0; i < lq->length; i++) {
				ele = curNode->data;
				printf("第%d个元素：%d\n", i+1, *ele);
				curNode = curNode->next;
			}
		}
		else
		{

		}
	}
	printf("\n");
}

void clearQueue()
{
	int ac = tryGetNum("确认清楚？(1.确认 other.取消)");
	if (ac != 1) {
		return;
	}
	if (testCase == AQ) {
		ClearAQueue(aq);
	}
	else
	{
		ClearLQueue(lq);
	}
}

void isEmptyQueue()
{
	


	if (testCase == AQ) {
		if (IsEmptyAQueue(aq)) {
			printf("空的队列!!!\n");
		}
		else
		{
			printf("非空的队列!!!\n");
		}
	}
	else
	{
		if (IsEmptyLQueue(lq)) {
			printf("空的队列!!!\n");
		}
		else
		{
			printf("非空的队列!!!\n");
		}
	}
}

void isFullQueue()
{
	if (IsFullAQueue(aq)) {
		printf("满的队列!!!\n");
	}
	else
	{
		printf("未满的队列!!!\n");
	}
}

void getHeadEle()
{
	int head;
	if (testCase == AQ) {
		if (GetHeadAQueue(aq, &head)) {
			printf("\n队首元素：%d\n", head);
		}
		else
		{
			printf("\n获取队首元素失败!!!\n");
		}
	}
	else
	{
		if (GetHeadLQueue(lq, &head)) {
			printf("\n队首元素：%d\n", head);
		}
		else
		{
			printf("\n获取队首元素失败!!!\n");
		}
	}
}

Status getCode()
{
	char str[64] = { 0 };
	printf("\n请输入命令：(allcode 察看所有可用命令)\n");
	scanf("%s", str);
	if (testCase == AQ) {
		if (comparStr(str, "allcode")) {
			printf("\n");
			printf("cls-------------清屏\n");
			printf("end-------------结束测试\n");
			printf("isempty---------是否为空队列\n");
			printf("isfull----------是否为满队列\n");
			printf("clear-----------清楚队列\n");
			printf("showhead--------察看首元素\n");
			printf("showall---------察看所有元素\n");
			printf("dequeue---------出队一个元素\n");
			printf("enqueue---------入队一个元素\n");
			printf("\n");
		}
		else if (comparStr(str, "cls"))
		{
			system("cls");
			return TRUE;
		}
		else if(comparStr(str,"end"))
		{
			return FALSE;
		}
		else if (comparStr(str, "isempty"))
		{
			isEmptyQueue();
			return TRUE;
		}
		else if (comparStr(str, "isfull"))
		{
			isFullQueue();
			return TRUE;
		}
		else if (comparStr(str, "clear"))
		{
			clearQueue();
			return TRUE;
		}
		else if (comparStr(str, "showhead"))
		{
			getHeadEle();
			return TRUE;
		}
		else if (comparStr(str, "showall"))
		{
			showAllQueue();
			return TRUE;
		}
		else if (comparStr(str, "dequeue"))
		{
			DeQueueAndShow();
			return TRUE;
		}
		else if (comparStr(str, "enqueue"))
		{
			int ele = tryGetNum("请输入一个元素值：");
			EnQueue(ele);
			return TRUE;
		}
		else
		{
			printf("\n无法解析的命令!!!\n");
			return TRUE;
		}
	}
	else
	{
		if (comparStr(str, "allcode")) {
			printf("\n");
			printf("cls-------------清屏\n");
			printf("end-------------结束测试\n");
			printf("isempty---------是否为空队列\n");
			printf("clear-----------清楚队列\n");
			printf("showhead--------察看首元素\n");
			printf("showall---------察看所有元素\n");
			printf("dequeue---------出队一个元素\n");
			printf("enqueue---------入队一个元素\n");
			printf("\n");
		}
		else if (comparStr(str, "cls"))
		{
			system("cls");
			return TRUE;
		}
		else if (comparStr(str, "end"))
		{
			return FALSE;
		}
		else if (comparStr(str, "isempty"))
		{
			isEmptyQueue();
			return TRUE;
		}
		else if (comparStr(str, "clear"))
		{
			clearQueue();
			return TRUE;
		}
		else if (comparStr(str, "showhead"))
		{
			getHeadEle();
			return TRUE;
		}
		else if (comparStr(str, "showall"))
		{
			showAllQueue();
			return TRUE;
		}
		else if (comparStr(str, "dequeue"))
		{
			DeQueueAndShow();
			return TRUE;
		}
		else if (comparStr(str, "enqueue"))
		{
			int ele = tryGetNum("请输入一个元素值：");
			EnQueue(ele);
			return TRUE;
		}
		else
		{
			printf("\n无法解析的命令!!!\n");
			return TRUE;
		}

	}
	
}

