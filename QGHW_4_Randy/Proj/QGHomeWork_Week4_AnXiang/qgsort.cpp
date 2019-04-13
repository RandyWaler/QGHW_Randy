#include "stdafx.h"
#include "qgsort.h"

//各种排序算法合集
//从小到大排序 
//--------------------------
void swap(int* a, int* b) {
	if (*a == *b) {
		return;
	}
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}
//--------------------------
//冒泡排序
void BubbleSort(int arry[], int length) {
	for (int i = 0; i<length; i++) {
		for (int j = 0; j<length - i - 1; j++) {
			if (arry[j]>arry[j + 1]) {
				swap(&arry[j], &arry[j + 1]);
			}
		}
	}
}
//--------------------------
//插入排序
void InsertionSort(int arry[], int length) {
	int temp;
	int pos;
	for (int i = 1; i <= length - 1; i++) {
		temp = arry[i];
		pos = i;
		for (int j = i - 1; j >= 0; j--) {
			if (arry[j]>temp) {
				pos = j;
			}
			else {
				break;
			}
		}
		for (int j = i; j>pos; j--) {
			arry[j] = arry[j - 1];
		}
		arry[pos] = temp;
	}
}
//---------------------------------------
//选择排序
void SelectionSort(int arry[], int length) {//单向选择 
	int pos;
	for (int i = 0; i<length; i++) {
		pos = i;
		for (int j = i + 1; j<length; j++) {
			if (arry[pos]>arry[j]) {
				pos = j;
			}
		}
		swap(&arry[i], &arry[pos]);
	}
}
void DoubleSelectionSort(int arry[], int length) {//双向选择
	int posMin;
	int posMax;
	for (int i = 0; i<length / 2; i++) {
		posMin = i;
		posMax = length - i - 1;
		if (arry[i]>arry[length - i - 1]) {
			swap(&arry[i], &arry[length - i - 1]);
		}
		for (int j = i + 1; j<length - i - 1; j++) {
			if (arry[posMin]>arry[j]) {
				posMin = j;
			}
			if (arry[posMax]<arry[j]) {
				posMax = j;
			}
		}
		swap(&arry[i], &arry[posMin]);
		swap(&arry[length - i - 1], &arry[posMax]);
	}

}
//-------------------------------------
//快速排序
void QuickSort_Recursion(int arry[], int start, int end) {//使用递归的快速排序

	if (start >= end) {
		return;
	}

	int flag = start;
	for (int i = start; i<end; i++) {
		if (arry[i]<arry[end]) {
			swap(&arry[flag], &arry[i]);
			flag++;
		}
	}

	swap(&arry[flag], &arry[end]);

	QuickSort_Recursion(arry, start, flag - 1);
	QuickSort_Recursion(arry, flag + 1, end);
}
void QuickSort_Recursion(int arry[], int length){//使用递归的快速排序
	QuickSort_Recursion(arry, 0, length - 1);
}

void QuickSort(int * arry, int length) {//使用循环的快速排序

	int start = 0;
	int end = length - 1;
	bool *arryFlag = (bool*)malloc(sizeof(bool)*length);
	for (int i = 0; i < length; i++) {
		arryFlag[i] = false;
	}
	int flag = 0;
lqs:
	if (start >= end) {
		arryFlag[start] = true;
		goto lqscheck;
	}

	flag = start;
	for (int i = start; i<end; i++) {
		if (arry[i]<arry[end]) {
			swap(&arry[flag], &arry[i]);
			flag++;
		}
	}

	swap(&arry[flag], &arry[end]);

	arryFlag[flag] = true;

lqscheck:
	for (int i = 0; i < length; i++) {
		if (!arryFlag[i]) {
			start = i;
			end = i;
			for (int j = i + 1; i < length; j++) {
				if (arryFlag[j]) {
					end = j - 1;
					break;
				}
			}
			goto lqs;
		}
	}


	free(arryFlag);
}

//-----------------------------------------------
//希尔排序
void ShellSort(int arry[], int length) {
	int grop = length / 2;
	while (grop) {
		int temp;
		int pos;
		for (int i = 0; i<grop; i++) {
			for (int j = i + grop; j<length; j += grop) {
				temp = arry[j];
				pos = j;
				for (int k = j - grop; k >= 0; k -= grop) {
					if (arry[k]>temp) {
						pos = k;
					}
					else {
						break;
					}
				}
				for (int k = j; k>pos; k -= grop) {
					arry[k] = arry[k - grop];
				}
				arry[pos] = temp;
			}
		}
		grop /= 2;
	}
}
//------------------------------------------------
//归并排序 

void Marge(int arry[], int start, int middle, int end) {
	int i, j, k;
	int n1 = middle - start + 1;
	int n2 = end - middle;
	int *arry_a = (int*)malloc(sizeof(int)*n1);
	int *arry_b = (int*)malloc(sizeof(int)*n2);

	for (i = 0; i<n1; i++) {
		arry_a[i] = arry[start + i];
	}
	for (j = 0; j<n2; j++) {
		arry_b[j] = arry[middle + j + 1];
	}
	i = 0; j = 0; k = start;
	while (i<n1&&j<n2) {
		if (arry_a[i] <= arry_b[j]) {
			arry[k] = arry_a[i];
			i++;
		}
		else {
			arry[k] = arry_b[j];
			j++;
		}
		k++;
	}
	while (i<n1) {
		arry[k] = arry_a[i];
		i++;
		k++;
	}
	while (j<n2) {
		arry[k] = arry_b[j];
		j++;
		k++;
	}
	free(arry_a);
	free(arry_b);

}
void MargeSort(int arry[], int start, int end) {
	if (start<end) {
		int middle = start + (end - start) / 2;
		MargeSort(arry, start, middle);
		MargeSort(arry, middle + 1, end);
		Marge(arry, start, middle, end);
	}
}
void MargeSort(int arry[], int length) {
	MargeSort(arry, 0, length - 1);
}
//------------------------------------------------
//计数排序
void setCountArry(int *carry, int length) {
	for (int i = 1; i < length; i++) {
		carry[i] += carry[i - 1];
	}
}
int getCountKFlag(int * carry,int k) {//获取计数序列第k个下标对应的下标值
	carry[k]--;
	return carry[k];
}
void CountSort(int ** arry, int length, int min,int max)//计数排序
{
	int *countArry = (int*)malloc(sizeof(int)*(max - min + 1));
	//清0计数数组
	for (int i = 0; i < max - min+1; i++) {
		countArry[i] = 0;
	}
	//累计计数数组
	for (int i = 0; i < length; i++) {
		countArry[(*arry)[i]-min]++;
	}
            
	//这里可能比较的数组并不是int 而是obj的一个字段，因此不能直接对原数组进行直接重写，由于在obj数组排序的情况下需要进行拷贝构造
	//因而需要建立新的数组，根据计数数组，从原数组中依次将元素放到排序好后的位置
	//新建数组 
	int *newArry=(int*)malloc(sizeof(int)*length);
	//设定好计数数组
	setCountArry(countArry, max - min + 1);
	//构建排序好的数组
	for (int i = length-1; i >=0; i--) {
		newArry[getCountKFlag(countArry, (*arry)[i] - min)] = (*arry)[i];
	}
	free(*arry);//释放原数组
	*arry = newArry;//更改传入的二级指针所指向的数组指针到新构建出的数组
	free(countArry);
}
void CountSort(int ** arry, int length)
{
	CountSort(arry, length, 0, length - 1);
}
//------------------------------------------------
//基数排序
void RadixCountSort(int ** arry, int length)
{
	
	bool isBit = false;//是否在当前位数上获得过有效位

	for (int nbNumber = 1;; nbNumber++) {
		isBit = false;
		int bitN[19] = { 0 };//我们这里使用针对每个位上数字的计数排序（-9到9 19个数字），而不是用数组去装（节约空间）
		for (int i = 0; i < length; i++) {
			int nbtime = nbNumber;
			int gnum = ((*arry)[i]);
			while (nbtime-1)
			{
				gnum = gnum / 10;
				nbtime--;
			}
			gnum = gnum % 10;
			bitN[gnum+9]++;
			if (abs(((*arry)[i]))>=(int)pow(10,nbNumber-1)) {
				isBit = true;
			}
		}
		if (!isBit) {//如果某位上全是0，则已经完成排序
			
			break;
		}
		int *newArry = (int*)malloc(sizeof(int)*length);
		setCountArry(bitN, 19);
		//构建排序好的数组
		for (int i = length-1; i >= 0; i--) {
			int nbtime = nbNumber;
			int gnum = ((*arry)[i]);
			while (nbtime - 1)
			{
				gnum = gnum / 10;
				nbtime--;
			}
			gnum = gnum % 10;
			newArry[getCountKFlag(bitN, gnum+9)] = (*arry)[i];
		}
		free(*arry);//释放原数组
		*arry = newArry;//更改传入的二级指针所指向的数组指针到新构建出的数组
		
	}
}
//void RadixCountSort(int ** arry, int length)
//{
//
//	bool isBit = false;//是否在当前位数上获得过有效位
//
//	for (int nbNumber = 1;; nbNumber++) {
//		isBit = false;
//		int bitN[10] = { 0 };//我们这里使用针对每个位上数字的计数排序，而不是用桶去装（节约空间）
//		for (int i = 0; i < length; i++) {
//			int nbtime = nbNumber;
//			int gnum = ((*arry)[i]);
//			while (nbtime - 1)
//			{
//				gnum = gnum / 10;
//				nbtime--;
//			}
//			gnum = gnum % 10;
//			bitN[gnum]++;
//			if (((*arry)[i])>(int)pow(10, nbNumber - 1)) {
//				isBit = true;
//			}
//		}
//		if (!isBit) {//如果某位上全是0，则已经完成排序
//
//			break;
//		}
//		int *newArry = (int*)malloc(sizeof(int)*length);
//		setCountArry(bitN, 10);
//		构建排序好的数组
//		for (int i = length - 1; i >= 0; i--) {
//			int nbtime = nbNumber;
//			int gnum = ((*arry)[i]);
//			while (nbtime - 1)
//			{
//				gnum = gnum / 10;
//				nbtime--;
//			}
//			gnum = gnum % 10;
//			newArry[getCountKFlag(bitN, gnum)] = (*arry)[i];
//		}
//		free(*arry);//释放原数组
//		*arry = newArry;//更改传入的二级指针所指向的数组指针到新构建出的数组
//
//	}
//}
//------------------------------------------------
//颜色排序
void ColorSort(int * arry, int length)
{
	int spos = 0;
	int epos = length - 1;

	for (int i = 0; i<=epos; i++) {
		if (arry[i] == 0) {
			if (i > spos) {
				swap(&arry[i], &arry[spos]);
				spos++;
				i--;
				continue;
			}
		}
		else if (arry[i] == 2) {
			swap(&arry[i],&arry[epos]);
			epos--;
			i--;
			continue;
		}
	}
}
//------------------------------------------------
//在无序数组中找到第k个元素
int kFindSortMin(int *arry, int start, int end, int k)
{
	int flag = start;
	for (int i = start; i < end; i++) {
		if (arry[i] < arry[end]) {
			swap(&arry[flag], &arry[i]);
			flag++;
		}
	}
	swap(&arry[flag], &arry[end]);

	if (flag == k) {
		return arry[flag];
	}
	else if(flag>k)
	{
		return kFindSortMin(arry, start, flag-1,k);
	}
	else
	{
		return kFindSortMin(arry, flag+1, end, k);
	}
}
int kFindSortMax(int *arry, int start, int end, int k)
{
	int flag = start;
	for (int i = start; i < end; i++) {
		if (arry[i] > arry[end]) {
			swap(&arry[flag], &arry[i]);
			flag++;
		}
	}
	swap(&arry[flag], &arry[end]);

	if (flag == k) {
		return arry[flag];
	}
	else if (flag>k)
	{
		return kFindSortMax(arry, start, flag - 1, k);
	}
	else
	{
		return kFindSortMax(arry, flag + 1, end, k);
	}
}
int kFindSort(int * arry, int length, int k,bool flag)
{
	if (k > length||k-1<0) {
		std::cout << "error：k值超过数组长度或小于0!!!" << std::endl;
		return -1;
	}
	if (flag) {
		return kFindSortMin(arry, 0, length - 1, k - 1);
	}
	else
	{
		return kFindSortMax(arry, 0, length - 1, k - 1);
	}

}
