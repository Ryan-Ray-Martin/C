/*
 * C Program to Implement Quick Sort Using Randomization
 */
#include <stdio.h>
#include <time.h>
#include <math.h>

int main()
{
  time_of_small_quicksort();
  time_of_medium_quicksort();
  time_of_large_quicksort();
}

void small_array(int arr[])
{
    int SMALL = 10000;


    srand(0);
    int i, j;
    for (i = SMALL - 1; i > 0; i--)
      j = rand();
}

void medium_array(int arr[])
{
    int MEDIUM = 100000;


    srand(0);
    int i, j;
    for (i = MEDIUM - 1; i > 0; i--)
      j = rand();
}

void large_array(int arr[])
{
    int LARGE = 1000000;


    srand(time(NULL));
    int i, j, temp;
    for (i = LARGE - 1; i > 0; i--)
        j = rand()%(i + 1);
        
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partion(int arr[], int p, int r)
{
    int pivotIndex = p + rand()%(r - p + 1); //uses a random number as a pivot
    int pivot;
    int i = p - 1;
    int j;
    pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[r]);
    for (j = p; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }

    }
    swap(&arr[i+1], &arr[r]);
    return i + 1;
}

void quick_sort(int arr[], int p, int q)
{
    int j;
    if (p < q)
    {
        j = partion(arr, p, q);
        quick_sort(arr, p, j-1);
        quick_sort(arr, j+1, q);
    }
}


int quicksort_small()
{

    int i;
    int SMALL = 10000;
    int arr[SMALL];
    for (i = 0; i < SMALL; i++)
        arr[i] = i;
    small_array(arr); //To make a random array to be sorted
    quick_sort(arr, 0, SMALL-1); //does quicksort on the random array
    for (i = 0; i < SMALL; i++)
      //un-comment to see sorted array
      // printf("%d \n", arr[i]);
    return 0;
}

int quicksort_medium()
{
    int MEDIUM = 100000;
    int i;
    int arr[MEDIUM];
    for (i = 0; i < MEDIUM; i++)
        arr[i] = i;
    medium_array(arr); //To make a random array to be sorted
    quick_sort(arr, 0, MEDIUM-1); //does quicksort on the random array
    for (i = 0; i < MEDIUM; i++)
      // un-comment to see sorted array
      // printf("%d \n", arr[i]);
    return 0;
}
int quicksort_large()
{
    int LARGE = 1000000;
    int i;
    int arr[LARGE];
    for (i = 0; i < LARGE; i++)
        arr[i] = i;
    large_array(arr); //To make a random array to be sorted
    quick_sort(arr, 0, LARGE-1); //does quicksort on the random array
    for (i = 0; i < LARGE; i++)
      // un-comment to see sorted array
      //      printf("%d \n", arr[i]);
    return 0;
}
int time_of_small_quicksort()
{
    clock_t begin = clock();
    quicksort_small();
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of SMALL quicksort with an array size of 10000: %f seco\
nds\n", time_spent);
}
int time_of_medium_quicksort()
{
    clock_t begin = clock();
    quicksort_medium();
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of MEDIUM quicksort with an array size of 100000: %f seco\
\                                                                               
nds\n", time_spent);
}
int time_of_large_quicksort()
{
    clock_t begin = clock();
    quicksort_large();
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of LARGE quicksort  sort with an array size of 1000000: %f seco\
\                                                                               
nds\n", time_spent);
}
