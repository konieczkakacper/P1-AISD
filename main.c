#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ns[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

int argMin(int *A, int begin, int end) // szukanie najniższego argumentu uzyte w selectionSort
{
    int marg = begin;
    int i;
    for(i = begin + 1; i < end; i++)
    {
        if(A[i] < A[marg])
        {
            marg = i;
        }
    }
    return  marg;
}

void swap(int *A, int i, int j) //uzyte w selectionSort
{
    int tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}


void fillRandom(int *A, int n)  //generuje randomowe liczby
{
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % n;
    }
}

void fillIncreasing(int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = i;
    }
}

void fillDecreasing(int *A, int n)
{
    int i;
    for (i = n; i >= 0; i--)
    {
        A[n - i] = i;
    }
}

void fillVshape(int *A, int n)
{
    int i;
    for (i = n; i >= n / 2; i--)
    {
        A[n - i] = i;
    }
    i = 0;
    for(i = n /2 +1; i < n; i++)
    {
        A[i] = i;
    }
}

void selectionSort(int *A, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        int j;
        j = argMin(A, i, n);
        swap(A,i,j);

    }
}

void insertionSort(int *A, int n)
{
    int i,j;
    for(j = 1; j < n; j++)
    {
        int key = A[j];
        i = j -1;
        while(i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i -= 1;
        }
        A[i + 1] = key;
    }
}


int partition(int *A, int p, int r) //funkcja wykorzystana w funkcji quickSort
{
    int x = A[r];
    int i = p - 1;
    int j;
    for(j = p; j < r; j++)
    {
        if(A[j] <= x)
        {
           i++;
           swap(A, i, j);
        }
    }
    i++;
    swap(A, i, r);
    return i;
}
        
        
    

void quickSort(int *A, int p, int r) // działa do random all oraz dla increasing do 30k (bez komendy w CMakeLists.txt do zwiększania stosu)
{
    if(p < r)
    {
       int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r); 
    }
}

void quickSortAll(int *A, int n)
{
    quickSort(A, 0, n - 1);
}

int irandom(int p, int r)
{
    return p + rand() % (r - p);
}

int randomizedPartition(int *A, int p, int r)    
{
    int i = irandom( p,r);
    swap(A, i, r);
    return partition(A, p, r);
}


void randomizedQuickSort(int *A, int p, int r)
{
    int q;
    if(p < r)
    {
        q = randomizedPartition(A, p, r);
        randomizedQuickSort(A, p, q - 1);
        randomizedQuickSort(A, q + 1, r);
    }
}

void randomizedQuickSortAll(int *A, int n)
{
    randomizedQuickSort(A, 0, n - 1);
}

// HEAP SORT i funkcje pomocnicze:

int left(int i)
{
    return (2 * i) + 1;
}

int right(int i)
{
    return (2 * i) + 2;
}

void maxHeapify(int *A, int i, int size)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if(l < size && A[l] > A[largest])
    {
        largest = l;
    }

    if((r < size) && (A[r] > A[largest]))
    {
        largest = r;
    }

    if(largest != i)
    {
        swap(A, i, largest);
        maxHeapify(A, largest, size);
    }
}

void buildMaxHeap(int *A, int n)
{
    int i;
    for(i = n / 2 - 1; i >= 0; i-- )
    {
        maxHeapify(A, i, n);
    }
}

void heapSort(int *A, int n)
{
   buildMaxHeap(A, n);

   int i;
    for(i = n - 1; i > 0; i--)
    {
        swap(A,0,i);
        maxHeapify(A, 0, i);
    }
}

//funkcje sprawdzające działanie projektu

bool isRandom(int *A, int n)
{
    return true;
}

bool isIncreasing(int *A, int n)
{
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isDecreasing(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] >= A[i - 1])
        {
            return false;
        }
    }
    return true;
}

bool isVshape(int *A, int n)
{
    if (n % 2 == 0)
    {
        return isDecreasing(A, n/2) && isIncreasing(A + n/2, n/2);
    }
    return isDecreasing(A, n/2 + 1) && isIncreasing(A + n/2, n/2 + 1);
}

bool isSorted(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (A[i] < A[i - 1])
        {
            return false;
        }
    }
    return true;
}

char *boolToString(bool b)
{

    return b ? "Y" : "N";
}

void (*fill_functions[])(int *, int) = { fillRandom, fillIncreasing, fillDecreasing, fillVshape };
bool (*check_functions[])(int *, int) = { isRandom, isIncreasing, isDecreasing, isVshape };
void (*sort_functions[])(int *, int) = { selectionSort, insertionSort, quickSortAll, randomizedQuickSortAll, heapSort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "RandomizedQuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++)
    {
        void (*sort)(int *, int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++)
        {
            void (*fill)(int *, int) = fill_functions[j];
            bool (*check)(int *, int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++)
            {
                int n = ns[k];
                int *A = calloc(n, sizeof(*A));

                fill(A, n);
                bool is_filled_ok = check(A, n);

                clock_t begin = clock();
                sort(A, n);
                clock_t end = clock();
                double seconds = (double) (end - begin) / (double) CLOCKS_PER_SEC;

                bool isSortedOk = isSorted(A, n);

                printf("%-20s %-11s %-10d %-4s %-4s %g\n", sort_names[i], fill_names[j], n,
                       boolToString(is_filled_ok), boolToString(isSortedOk), seconds);
                // wyświetla czasy sortowania
                free(A);
            }
        }
    }
    return 0;
}
