/*
把八大排序算法都放进来
Insert Sort--直接插入排序
Shell Sort--希尔排序
Select Sort--简单选择排序
Merge Sort--归并排序
Quick Sort--快速排序
*/
#include "stdafx.h"
#include <iostream>
#define LEN 7

void SelectSort(int* num, int length);
void display(int* num, int len);
void InsertSort(int* num, int len);
void ShellSort(int* num, int len);
void Mergesort(int* num, int start, int end);
void Combine(int* num, int start, int divide, int end);
int Dighole(int* num, int start, int end);
void Quicksort(int* num, int start, int end);

int main()
{
	using namespace std;
	int num[LEN] = { 2,0,1,9,4,3,4 };
	display(num, LEN);
	//Select sort
	SelectSort(num, LEN);
	cout << "Selest sort:" << endl;
	display(num, LEN);
	//Insert sort
	cout << "Insert sort:" << endl;
	int num2[LEN] = { 2,0,1,9,4,3,4 };
	InsertSort(num2, LEN);
	display(num2, LEN);
	//Shell sort
	cout << "Shell sort:" << endl;
	int num3[LEN] = { 2,0,1,9,4,3,4 };
	ShellSort(num3, LEN);
	display(num3, LEN);
	//Merge sort
	cout << "Merge sort: " << endl;
	int num4[LEN]= { 2,0,1,9,4,3,4 };
	Mergesort(num4, 0, LEN - 1);
	display(num4, LEN);
	//Merge sort
	cout << "Quick sort: " << endl;
	int num5[LEN+1] = { 0,2,0,1,9,4,3,4 };
	Quicksort(num5, 0, LEN );
	display(num5, LEN+1);
	system("pause");
    return 0;
}

void SelectSort(int* num, int len)//not done yet
{
	for (int head = 0; head < len; head++)
	{
		int min = *(num + head);
		int min_pos = head;
		int range;
		for (range = head; range < len; range++)
		{
			if (*(num + range) < min)
			{
				min_pos = range;
				min = *(num + range);
			}
		}
		if (min_pos != head)
		{
			*(num + min_pos) = *(num + head);
			*(num + head) = min;
		}
	}
}
void display(int* num, int len)
{
	for (int i = 0; i < len; i++)
		std::cout << *(num + i) << " ";
	std::cout << std::endl;
}
void InsertSort(int* num, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (*(num + j) < *(num + j - 1))
			{
				int temp = *(num + j);
				*(num + j) = *(num + j - 1);
				*(num + j - 1) = temp;
			}
		}
	}
}
void ShellSort(int* num, int len)
{
	for (int gap = len / 2; gap > 0; gap = gap / 2)
	{
		for (int i = 0; i < len / gap; i += gap)
		{
			for (int j = i; j > 0; j -= gap)
			{
				if (*(num + j) < *(num + j - gap))
				{
					int temp = *(num + j);
					*(num + j) = *(num + j - gap);
					*(num + j - gap) = temp;
				}
			}
		}
	}
}
void Mergesort(int* num, int start, int end)
{
	int gap = (start + end) / 2;
	if (start < end)
	{
		Mergesort(num, start, gap);
		Mergesort(num, gap + 1, end);
		Combine(num, start, gap, end);
	}
}
void Combine(int* num, int start, int divide, int end)
{
	//num[start]---------num[divide]
	//num[divide+1]----num[end]
	//combine them into one num[]
	int i = start;
	int j = divide + 1;
	int k = 0;
	int temp[LEN];
	while (i <= divide && j <= end)
	{
		if (*(num + i) <= *(num + j))
		{
			*(temp + k) = *(num + i);
			i++; k++;
		}
		else {
			*(temp + k) = *(num + j);
			j++; k++;
		}
	}
	for (i; i <= divide; i++, k++)
		*(temp + k) = *(num + i);
	for (j; j <= end; j++, k++)
		*(temp + k) = *(num + j);
	for (int r = 0; r <= end - start; r++)
		*(num + r + start) = temp[r];
}
void Quicksort(int* num, int start, int end)
{
	if (start < end)
	{
		int i = Dighole(num, start, end);
		Quicksort(num, start, i);
		Quicksort(num, i + 1, end);
	}
}
int DigHole(int* num, int first, int last) {
	int pivot = num[first];
	while (first < last) {
		while (first != last) {
			if (pivot > num[last]) {
				num[first] = num[last];
				first++;
				break;
			}
			last--;
		}
		while (first != last) {
			if (pivot < num[first]) {
				num[last] = num[first];
				last--;
				break;
			}
			first++;
		}
	}
	num[first] = pivot;
	return first;
}

/*以下是可以用用于stm32的Kalman滤波算法
	需要修改为一个kalman_filter函数
	变量q,p,r改为static double类型
	返回double result
	传递参数为当前读取数据[ ]及其长度len和result
	 
#include <stdio.h>

int main(void) {
	double data[20] = { 110,112,111,115,115,
		115,109,113,112,112,
		112,114,114,112,109,
		116,115,107,112,113, };
	double p = 1.0;
	double q = 0.000002;
	double r = 0.00025;
	int i;
	double gain;
	double result = 112;
	for (i = 0; i<20; i++)
	{
		p = p + q;
		gain = p / (p + r);
		result = result + (gain*(data[i] - result));
		p = (1 - gain)*p;
		printf("%.6f\n", result);
	}
	return 0;
}
*/

/*
----finished version
#include <stdio.h>

static double kalman_p=1.0;
static double kalman_q=0.000002;
static double kalman_r=0.00025;
double Kalman_fliter(double* data, int len, double result);

int main(void) {
	double data[20]={110,112,111,115,115,
									115,109,113,112,112,
									112,114,114,112,109,
									116,115,107,112,113,};
	int i;
	double gain;
	double result=110;
	result=Kalman_fliter(data+1,10,result);
	printf("%.6f\n",result);
	result=Kalman_fliter(data+11,5,result);
	printf("%.6f\n",result);
	printf("test");
	return 0;
}

double Kalman_fliter(double* data, int len, double result)
{
	int i=0;
	double gain;
	printf("p=%.6f, q=%.6f, r=%.6f\n",kalman_p,kalman_q,kalman_r);
	for(i;i<len;i++)
	{
		kalman_p=kalman_p+kalman_q;
		gain=kalman_p/(kalman_p+kalman_r);
		result=result+(gain*(*(data+i)-result));
		kalman_p=(1-gain)*kalman_p;
	}
	return result;
}
*/