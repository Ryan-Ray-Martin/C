
#include <stdio.h>
#include <time.h>
#include <math.h>


int main() {


   time_of_small_insertion_sort();
   time_of_medium_insertion_sort();
   time_of_large_insertion_sort();


}

int small() {

    srand(0);

    int i;
    int SMALL = 10000;
    int array[SMALL];


    for(i = 1; i < SMALL + 1; i ++){
        array[i] = rand();
    //un-comment section below to see printed array:
     //   printf("%d\n", array[i]);
    }

    return 0;

}

int medium(){

    srand(0);

    int i;
    int MEDIUM = 100000;
    int array[MEDIUM];


    for(i = 1; i < MEDIUM + 1; i ++){
        array[i] = rand();
    //un-comment section below to see printed array:
       // printf("value of a: %d\n", array[i]);
    }

    return array[i];



}

int large(){

    srand(0);

    int i;
    int LARGE = 1000000;
    int array[LARGE];


    for(i = 1; i < LARGE + 1; i ++){
        array[i] = rand();
    //un-comment section below to see printed array:
       // printf("value of a: %d\n", array[i]);
    }

    return array[i];


}

int insertionSortSmall()
{
    int SMALL = 10000;
    int i,j,n,key;
    int a[SMALL];

    for(j=2;j<=SMALL;j++)
    {
        key=a[j];
        i=j-1;

        while((key<a[i])&&(i>=0))
        {
            a[i+1]=a[i];    //moves element the next spot
            i=i-1;
        }

        a[i+1]=key;    //puts element in the correct location
        // in ascending order
    }

    return 0;

}

int insertionSortMedium()
{
    int MEDIUM = 100000;
    int i,j,n,key;
    int a[MEDIUM];

    for(j=2;j<=MEDIUM;j++)
    {
        key=a[j];
        i=j-1;

        while((key<a[i])&&(i>=0))
        {
            a[i+1]=a[i];    //moves element to the next spot
            i=i-1;
        }

        a[i+1]=key;    //puts element in the correct location
        // in ascending order
    }

    return 0;
}

int insertionSortLarge()
{
    int LARGE = 1000000;
    int i,j,n,key;
    int a[LARGE];

    for(j=2;j<=LARGE;j++)
    {
        key=a[j];
        i=j-1;

        while((key<a[i])&&(i>=0))
        {
            a[i+1]=a[i];    //moves element to the next spot
            i=i-1;
        }

        a[i+1]=key;    //puts element in the correct location
        // in ascending order
    }

    return 0;
}

int time_of_small_insertion_sort()
{
    clock_t begin = clock();
    insertionSortSmall(small());
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of SMALL insertion sort with an array size of 10000: %f seconds\n", time_spent);
}

int time_of_medium_insertion_sort()
{
    clock_t begin = clock();
    insertionSortMedium(medium());
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of MEDIUM insertion sort with an array size of 100000: %f seconds\n", time_spent);
}

int time_of_large_insertion_sort()
{
    clock_t begin = clock();
    insertionSortLarge(large());
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Time of LARGE insertion sort with an array size of 1000000: %f seconds\n", time_spent);
}
