#include "heap.h"

using namespace std;



int main()
{
    int heap[10];
    int size = 10;
    int min = 0, max = 100;
    int newValue;
    int lastIndex = -1;
    //fill in heap
    for (int i = 0; i < size; i++)
    {
        newValue = rand() % (max + 1 - min) + min;
        cout << newValue << " ";
        heap[i] = newValue;
        //insertHeap(heap, newValue, lastIndex);
    }
    cout << endl;
    heapify(heap, lastIndex, size);
    for (int i = 0; i < size; i++)
    {
        cout << heap[i] << " ";

    }
    cout << endl;
   /* for (int i = 0; i < size; i++)
    {
        cout << heap[0] << " ";
        deleteHeap(heap, lastIndex);
    }*/
    printHeap(heap, lastIndex);
    return 0;
}



// Program needs to be min heap with lowest number top.
//heap[] is actual heap, key is going to be inserted, the last index
// array is of a fixed size
void insertHeap(int heap[], int key, int &lastIndex)
{
    lastIndex++;
    heap[lastIndex] = key;
    reheapUp(heap, lastIndex);
}


void reheapUp(int heap[], int locIndex)
{
    if (locIndex == 0) //indicates we're at the root. Exit Recursion.
    {
        return;
    }


    int parentIndex = (locIndex - 1) / 2;

    //swap for max heap
    if (heap[parentIndex] > heap[locIndex])
    {
        int hold = heap[parentIndex];
        heap[parentIndex] = heap[locIndex];
        heap[locIndex] = hold;

        reheapUp(heap, parentIndex);
    }
}


void deleteHeap(int heap[], int &lastIndex)
{
    if (lastIndex < 0)
    {
        cout << "Heap is empty.";
    }

    heap[0] = heap[lastIndex];
    lastIndex--;

    reheapDown(heap, 0,lastIndex);


}

void reheapDown(int heap[], int locIndex, int lastIndex)
{
    int leftIndex, rightIndex, biggestIndex,leftValue,rightValue;

    leftIndex = 2 * locIndex + 1;



    if (leftIndex <= lastIndex) //means left child exists
    {
        leftValue = heap[leftIndex];
        rightIndex = leftIndex + 1;
        if (rightIndex <= lastIndex)
        {
            rightValue = heap[rightIndex];
        }
        else
        {
            //Have left child, but no right child.
            rightValue = leftValue - 1;//always less than leftvalue.
        }

        if (leftValue < rightValue)
        {
            biggestIndex = leftIndex;

        }
        else
        {
            biggestIndex = rightIndex;
        }
        //check if we should swap
        if (heap[biggestIndex] < heap[locIndex])
        {
            int hold = heap[locIndex];
            heap[locIndex] = heap[biggestIndex];
            heap[biggestIndex] = hold;
            reheapDown(heap, biggestIndex, lastIndex);
        }
    }
}

/*Write a function called heapify that takes an array of any length of random integers,
and converts it into a valid min heap.*/
//heap is an already made heap of some size. Random numbers.

//Heap does look like a min-heap after.
void heapify(int heap[], int &lastIndex, int size)
{
    int * dynamicArray;
    
    dynamicArray = new int[size];

    for (int i = 0; i < size; i++)
    {

        insertHeap(dynamicArray, heap[i], lastIndex);
    }
    for (int i = 0; i < size; i++)
    {
        heap[i] = dynamicArray[i];

    }
   
    delete[] dynamicArray;
}

void printHeap(int heap[], int lastIndex)
{
    int temp;
    int size = lastIndex;
    int *dynamicArray;
    dynamicArray = new int[size];

    for (int i = 0; i < lastIndex+1; i++)
    {
        dynamicArray[i] = heap[i];

    }
    for (int i = 0; i < size+1; i++)
    {
        cout << dynamicArray[0] << " ";
        deleteHeap(dynamicArray, lastIndex);
    }
    
}