/**************************************************************************//**
* @author Paul Hertfelder
*
*Testing done for 100,000 items
*Insert: ~5000ms
*Shell: 18ms
*quick: 13ms
*
* Program: Sorts using quick sort, shell sort, insert sort for an array of 
* random ints. First with twenty random numbers, then 100,000 random numbers.
* Then two thousand in order items through the three different sorts. 
*
* NOTE: Program will crash with higher in order numbers @ quick sort. 2,000
* items worked for this which took Insert 0ms Shell 0ms and Quick: 6ms..
/**************************************************************************/

#include "Sorts_Header.h"



/*For quickSort, shellSort use pseudocode on slides.*/

int main()
{
    cout << "Twenty random items: " << endl;
    TwentyItems();
    cout << "Hundred Thousand random items: " << endl;
    HundredThousand();
    cout << "Two Thousand in order items: " << endl;
    InOrder();
    return 0;
}



void TwentyItems()
{
    int *array = NULL;
    int *shellArray = NULL;
    int *quickArray = NULL;
    int *insertArray = NULL;
    int size;
    size = 20;
    array = new int[size];
    shellArray = new int[size];
    insertArray = new int[size];
    quickArray = new int[size];
    int p = 0;
    int r = size - 1;
    //If needed for hardcoding in size of arrays.
    /*int array[10000];

    int shellArray[10000];
    int quickArray[10000];
    int insertArray[10000];*/
    clock_t start, end;
    double milli_time;
    getRandomArray(array, size);
    copyArray(array, shellArray, quickArray, insertArray, size);
    /* cout << "Array: ";
     for (int i = 0; i < size; i++)
     {
         cout << array[i] << ", ";

     }*/
    start = clock();
    insertionSort(insertArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Insert Sort: " << milli_time << "ms\n" ;
    delete[]insertArray;

    start = clock();
    shellSort(shellArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    cout << fixed << setprecision(2) << "Shell Sort: " << milli_time << "ms\n";
    delete[]shellArray;

    start = clock();
    QuickSort(quickArray, p, r);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Quick Sort: " << milli_time << "ms\n" << endl;

    delete[] array;
    delete[]quickArray;
}


void HundredThousand()
{
    int *array = NULL;
    int *shellArray = NULL;
    int *quickArray = NULL;
    int *insertArray = NULL;
    int size;
    size = 100000;
    array = new int[size];
    shellArray = new int[size];
    insertArray = new int[size];
    quickArray = new int[size];
    int p = 0;
    int r = size - 1;
    //If needed for hardcoding in size of arrays.
    /*int array[10000];

    int shellArray[10000];
    int quickArray[10000];
    int insertArray[10000];*/
    clock_t start, end;
    double milli_time;
    getRandomArray(array, size);
    copyArray(array, shellArray, quickArray, insertArray, size);
    /* cout << "Array: ";
     for (int i = 0; i < size; i++)
     {
         cout << array[i] << ", ";

     }*/
    start = clock();
    insertionSort(insertArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Insert Sort: " << milli_time << "ms\n";
    delete[]insertArray;

    start = clock();
    shellSort(shellArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    cout << fixed << setprecision(2) << "Shell Sort: " << milli_time << "ms\n";
    delete[]shellArray;

    start = clock();
    QuickSort(quickArray, p, r);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Quick Sort: " << milli_time << "ms\n" << endl;

    delete[] array;
    delete[]quickArray;
}
void InOrder()
{
    int *array = NULL;
    int *shellArray = NULL;
    int *quickArray = NULL;
    int *insertArray = NULL;
    int size;
    size = 2000;
    array = new int[size];
    shellArray = new int[size];
    insertArray = new int[size];
    quickArray = new int[size];
    int p = 0;
    int r = size - 1;
    //If needed for hardcoding in size of arrays.
    /*int array[10000];

    int shellArray[10000];
    int quickArray[10000];
    int insertArray[10000];*/
    clock_t start, end;
    double milli_time;
    getSortedArray(array, size);
    copyArray(array, shellArray, quickArray, insertArray, size);
     
    start = clock();
    insertionSort(insertArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Insert Sort: " << milli_time << "ms\n";
    delete[]insertArray;

    start = clock();
    shellSort(shellArray, size);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    cout << fixed << setprecision(2) << "Shell Sort: " << milli_time << "ms\n";
    delete[]shellArray;

    start = clock();
    QuickSort(quickArray, p, r);
    end = clock();
    milli_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(2) << "Quick Sort: " << milli_time << "ms\n" << endl;

    delete[] array;
    delete[]quickArray;
}
void getSortedArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {

        array[i] = i;
    }
    return;
}
void getRandomArray(int array[], int size)
{
    int min = 0, max = 1000000; // or whatever bounds you wish
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % (max + 1 - min) + min;
    }
    return;
}

void copyArray(int array[], int shellArray[], int quickArray[], int insertArray[],int size)
{
    for (int i = 0; i < size; i++)
    {
        shellArray[i] = array[i];
        quickArray[i]= array[i];
        insertArray[i]= array[i];
    }
    return;
}

//insertion sort
//insert sort done.
void insertionSort(int insertArray[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        temp = insertArray[i];
        int j;
        for ( j = i; j > 0 && temp < insertArray[j - 1]; j--)
        {
            insertArray[j] = insertArray[j - 1];

        }
        insertArray[j] = temp;
    }
}

void shellSort(int list[],int size)
{
    int incre=size/2;
    int hold;
    int current;
    int walker;
    while (incre > 0)
    {
         current = incre;
         for (int i = current; i < size; i++)
         {
             hold = list[current];
             walker = current - incre;
             int j;
             while (walker >= 0 && hold < list[walker])
             {
                 list[walker + incre] = list[walker];
                 walker = walker - incre;
             }
             list[walker + incre] = hold;
             current = current + 1;

         }
         incre = incre / 2;
    }
    return;
}

void QuickSort(int A[], int p, int r)
{
    
    if (p < r)
    {
       int q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
    return;
}
int Partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p-1;
    int j;
    int temp;
    for (j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i = i + 1;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }

    }
    temp = A[i+1];
    A[i + 1] = A[r];
    A[r] = temp;
    return i + 1;

}