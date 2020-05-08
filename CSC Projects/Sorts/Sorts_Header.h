/**************************************************************************//**
* @author Paul Hertfelder
*
/**************************************************************************/

#ifndef _Sorts_Header_H_
#define _Sorts_Header_H_

#include <iostream>
#include <ctime>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
void TwentyItems();
void HundredThousand();
void InOrder();
void getSortedArray(int array[], int size);
void getRandomArray(int array[], int size);
void copyArray(int array[], int shellArray[], int quickArray[], int insertArray[],int size);

void insertionSort(int insertArry[], int size);
void shellSort(int list[], int size);
void QuickSort(int A[], int p, int r);
int Partition(int A[], int p, int r);



#endif _Sorts_Header_H_