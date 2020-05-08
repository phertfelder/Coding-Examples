#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <cstdlib>
#include <ctime>
void insertHeap(int heap[], int key, int &lastIndex);
void reheapUp(int heap[], int locIndex);
void deleteHeap(int heap[], int &lastIndex);
void reheapDown(int heap[], int locIndex, int lastIndex);
void heapify(int heap[], int &lastIndex, int size);
void printHeap(int heap[], int lastIndex);


#endif 
