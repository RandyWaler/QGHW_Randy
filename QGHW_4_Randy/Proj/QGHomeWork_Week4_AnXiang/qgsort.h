#pragma once


/**
*  @name        : void BubbleSort(int arry[], int length);
*  @description : ð������
*  @param       : ����ָ�� arry, ���鳤�� length
*/
void BubbleSort(int arry[], int length);
/**
 *  @name        : void InsertionSort(int arry[], int length);
 *  @description : ��������
 *  @param       : ����ָ�� arry, ���鳤�� length
 */
void InsertionSort(int arry[], int length);

/**
*  @name        : void SelectionSort(int arry[], int length);
*  @description : ����ѡ������
*  @param       : ����ָ�� arry, ���鳤�� length
*/
void SelectionSort(int arry[], int length);

/**
*  @name        : void DoubleSelectionSort(int arry[], int length);
*  @description : ˫��ѡ������
*  @param       : ����ָ�� arry, ���鳤�� length
*/
void DoubleSelectionSort(int arry[], int length);

/**
 *  @name        : void MargeSort(int arry[], int length);
 *  @description : �鲢����
 *  @param       : ����ָ�� arry, ���鳤�� length
 */
void MargeSort(int arry[], int length);

/**
*  @name        : void ShellSort(int arry[], int length);
*  @description : ϣ������
*  @param       : ����ָ�� arry, ���鳤�� length
*/
void ShellSort(int arry[], int length);


/**
 *  @name        : void QuickSort_Recursion(int arry[], int length);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��arry�����鳤�� length
 */
void QuickSort_Recursion(int arry[], int length);


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : �������򣨷ǵݹ�棩
 *  @param       : ����ָ��arry�����鳤�� length
 */
void QuickSort(int *a,int size);

/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : ��������
 *  @param       : ����ָ��arry�����鳤��length��Ĭ������Ϊ0�����鳤��-1��
 */
void CountSort(int **arry, int length);


/**
*  @name        : void CountSort(int *a, int size , int max)
*  @description : ��������
*  @param       : ����ָ��arry�����鳤��length����Сֵ min�����ֵ max
*/
void CountSort(int ** arry, int length, int min, int max);


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : ������������
 *  @param       : ����ָ��arry�����鳤��length
 */
void RadixCountSort(int **arry,int length);


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : ��ɫ����
 *  @param       : ����ָ��a��ֻ��0��1��2Ԫ�أ������鳤��length
 */
void ColorSort(int *arry,int length);


/**
 *  @name        : ����
 *  @description : ��һ�������������ҵ���K��/С����
 *  @param       : ����ָ��arry�����鳤��length����k��Ԫ�أ�true��С��� false�Ӵ���С
 */
int kFindSort(int *arry, int length, int k,bool flag);


