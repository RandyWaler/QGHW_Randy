#pragma once


/**
*  @name        : void BubbleSort(int arry[], int length);
*  @description : 冒泡排序
*  @param       : 数组指针 arry, 数组长度 length
*/
void BubbleSort(int arry[], int length);
/**
 *  @name        : void InsertionSort(int arry[], int length);
 *  @description : 插入排序
 *  @param       : 数组指针 arry, 数组长度 length
 */
void InsertionSort(int arry[], int length);

/**
*  @name        : void SelectionSort(int arry[], int length);
*  @description : 单向选则排序
*  @param       : 数组指针 arry, 数组长度 length
*/
void SelectionSort(int arry[], int length);

/**
*  @name        : void DoubleSelectionSort(int arry[], int length);
*  @description : 双向选则排序
*  @param       : 数组指针 arry, 数组长度 length
*/
void DoubleSelectionSort(int arry[], int length);

/**
 *  @name        : void MargeSort(int arry[], int length);
 *  @description : 归并排序
 *  @param       : 数组指针 arry, 数组长度 length
 */
void MargeSort(int arry[], int length);

/**
*  @name        : void ShellSort(int arry[], int length);
*  @description : 希尔排序
*  @param       : 数组指针 arry, 数组长度 length
*/
void ShellSort(int arry[], int length);


/**
 *  @name        : void QuickSort_Recursion(int arry[], int length);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针arry，数组长度 length
 */
void QuickSort_Recursion(int arry[], int length);


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针arry，数组长度 length
 */
void QuickSort(int *a,int size);

/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针arry，数组长度length（默认数据为0到数组长度-1）
 */
void CountSort(int **arry, int length);


/**
*  @name        : void CountSort(int *a, int size , int max)
*  @description : 计数排序
*  @param       : 数组指针arry，数组长度length，最小值 min，最大值 max
*/
void CountSort(int ** arry, int length, int min, int max);


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针arry，数组长度length
 */
void RadixCountSort(int **arry,int length);


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度length
 */
void ColorSort(int *arry,int length);


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针arry，数组长度length，第k个元素，true从小向大 false从大向小
 */
int kFindSort(int *arry, int length, int k,bool flag);


