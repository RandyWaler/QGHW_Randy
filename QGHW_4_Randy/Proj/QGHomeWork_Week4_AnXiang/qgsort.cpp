#include "stdafx.h"
#include "qgsort.h"

//���������㷨�ϼ�
//��С�������� 
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
//ð������
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
//��������
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
//ѡ������
void SelectionSort(int arry[], int length) {//����ѡ�� 
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
void DoubleSelectionSort(int arry[], int length) {//˫��ѡ��
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
//��������
void QuickSort_Recursion(int arry[], int start, int end) {//ʹ�õݹ�Ŀ�������

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
void QuickSort_Recursion(int arry[], int length){//ʹ�õݹ�Ŀ�������
	QuickSort_Recursion(arry, 0, length - 1);
}

void QuickSort(int * arry, int length) {//ʹ��ѭ���Ŀ�������

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
//ϣ������
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
//�鲢���� 

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
//��������
void setCountArry(int *carry, int length) {
	for (int i = 1; i < length; i++) {
		carry[i] += carry[i - 1];
	}
}
int getCountKFlag(int * carry,int k) {//��ȡ�������е�k���±��Ӧ���±�ֵ
	carry[k]--;
	return carry[k];
}
void CountSort(int ** arry, int length, int min,int max)//��������
{
	int *countArry = (int*)malloc(sizeof(int)*(max - min + 1));
	//��0��������
	for (int i = 0; i < max - min+1; i++) {
		countArry[i] = 0;
	}
	//�ۼƼ�������
	for (int i = 0; i < length; i++) {
		countArry[(*arry)[i]-min]++;
	}
            
	//������ܱȽϵ����鲢����int ����obj��һ���ֶΣ���˲���ֱ�Ӷ�ԭ�������ֱ����д��������obj����������������Ҫ���п�������
	//�����Ҫ�����µ����飬���ݼ������飬��ԭ���������ν�Ԫ�طŵ�����ú��λ��
	//�½����� 
	int *newArry=(int*)malloc(sizeof(int)*length);
	//�趨�ü�������
	setCountArry(countArry, max - min + 1);
	//��������õ�����
	for (int i = length-1; i >=0; i--) {
		newArry[getCountKFlag(countArry, (*arry)[i] - min)] = (*arry)[i];
	}
	free(*arry);//�ͷ�ԭ����
	*arry = newArry;//���Ĵ���Ķ���ָ����ָ�������ָ�뵽�¹�����������
	free(countArry);
}
void CountSort(int ** arry, int length)
{
	CountSort(arry, length, 0, length - 1);
}
//------------------------------------------------
//��������
void RadixCountSort(int ** arry, int length)
{
	
	bool isBit = false;//�Ƿ��ڵ�ǰλ���ϻ�ù���Чλ

	for (int nbNumber = 1;; nbNumber++) {
		isBit = false;
		int bitN[19] = { 0 };//��������ʹ�����ÿ��λ�����ֵļ�������-9��9 19�����֣���������������ȥװ����Լ�ռ䣩
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
		if (!isBit) {//���ĳλ��ȫ��0�����Ѿ��������
			
			break;
		}
		int *newArry = (int*)malloc(sizeof(int)*length);
		setCountArry(bitN, 19);
		//��������õ�����
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
		free(*arry);//�ͷ�ԭ����
		*arry = newArry;//���Ĵ���Ķ���ָ����ָ�������ָ�뵽�¹�����������
		
	}
}
//void RadixCountSort(int ** arry, int length)
//{
//
//	bool isBit = false;//�Ƿ��ڵ�ǰλ���ϻ�ù���Чλ
//
//	for (int nbNumber = 1;; nbNumber++) {
//		isBit = false;
//		int bitN[10] = { 0 };//��������ʹ�����ÿ��λ�����ֵļ������򣬶�������Ͱȥװ����Լ�ռ䣩
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
//		if (!isBit) {//���ĳλ��ȫ��0�����Ѿ��������
//
//			break;
//		}
//		int *newArry = (int*)malloc(sizeof(int)*length);
//		setCountArry(bitN, 10);
//		��������õ�����
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
//		free(*arry);//�ͷ�ԭ����
//		*arry = newArry;//���Ĵ���Ķ���ָ����ָ�������ָ�뵽�¹�����������
//
//	}
//}
//------------------------------------------------
//��ɫ����
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
//�������������ҵ���k��Ԫ��
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
		std::cout << "error��kֵ�������鳤�Ȼ�С��0!!!" << std::endl;
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
