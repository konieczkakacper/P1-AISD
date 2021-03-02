#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ns[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

int argmin(int *A, int begin, int end) // szukanie najniższego argumentu
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

void swap(int *A, int i, int j)
{
    int tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void fill_random(int *A, int n)  //generuje randomowe liczby na 3
{
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % n;
    }
}

void fill_increasing(int *A, int n) // TODO: implement na 3 zrobione
{
    int i;
    for (i = 0; i < n; i++)
    {
        A[i] = i;
    }
}

void fill_decreasing(int *A, int n) // TODO: implement na 3 zrobione
{
    int i;
    for (i = n; i >= 0; i--)
    {
        A[n - i] = i;
    }
}

void fill_vshape(int *A, int n) // TODO: implement na 3 zrobione
{
    int i;
    for (i = n; i >= n / 2; i--)
    {
        A[n - 1] = i;
    }
    i = 0;
    for(i = n /2 +1; i < n; i++)
    {
        A[i] = i;
    }
}

void selection_sort(int *A, int n) //TODO : dopisac do tego function min i swap (implement) na 3
{
    int i;
    for(i = 0; i < n; i++)
    {
        int j;
        j = argmin;

    }
}

void insertion_sort(int *A, int n)
{
    // TODO: implement na 3.5
}

void quick_sort(int *A, int p, int r)
{
    // TODO: implement na 4.0
} //

void quick_sort_all(int *A, int n)
{
    quick_sort(A, 0, n - 1);
}

void randomized_quick_sort(int *A, int p, int r)
{
    // TODO: implement na 4
   /* if(p < r)
    {
        randomized_quick_sort(A,p,q-1);  //FIXME: próba przepisania pseudo kodu dopisac reszre funkcji
        randomized_quick_sort(A,q+1,r);
    } */
}

void randomized_quick_sort_all(int *A, int n)
{
    randomized_quick_sort(A, 0, n - 1);
}

void heap_sort(int *A, int n)
{
    // TODO na 5
}

bool is_random(int *A, int n)
{
    return true;
}

bool is_increasing(int *A, int n) //funkcja sprawdzająca
{
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_decreasing(int *A, int n) //funkcja sprawdzająca
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

bool is_vshape(int *A, int n) // funkcja sprawdzająca
{
    if (n % 2 == 0)
    {
        return is_decreasing(A, n/2) && is_increasing(A + n/2, n/2);
    }
    return is_decreasing(A, n/2 + 1) && is_increasing(A + n/2, n/2 + 1);
}

bool is_sorted(int *A, int n)
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

char *bool_to_string(bool b)  // funkcja sprawdzająca
{
    return b ? "Y" : "N";
}

void (*fill_functions[])(int *, int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
bool (*check_functions[])(int *, int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, int) = { selection_sort, insertion_sort, quick_sort_all, randomized_quick_sort_all, heap_sort };

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

                clock_t begin = clock(); //startuje pomiar czasu wykonywania się funkcji
                sort(A, n);
                clock_t end = clock();
                double seconds = (double) (end - begin) / (double) CLOCKS_PER_SEC;

                bool is_sorted_ok = is_sorted(A, n);

                printf("%-20s %-11s %-10d %-4s %-4s %g\n", sort_names[i], fill_names[j], n,
                       bool_to_string(is_filled_ok), bool_to_string(is_sorted_ok), seconds);
                // wyświetla czasy sortowania
                free(A);
            }
        }
    }
    return 0;
}