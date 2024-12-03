#include<stdio.h>

int* takeMemory(int n)
{
    int *a;
    a = (int*)calloc(n, sizeof(int));
    return a;
}

void takeArray(int *a, int n)
{
    int i;
    for(i = 0; i<n; i++)
    {
        scanf("%d", a + i);
    }
}

void printArray(int *a, int n)
{
    int i;
    for(i = 0; i<n; i++)
    {
        printf("%d\n", *(a+i));
    }
}

int main()
{
    int *a;
    /*
        ///for(int i=0;;i++)
        ///a = (int*)malloc(5 * sizeof(int));
        a = (int*)calloc(5, sizeof(int));

        *a = 500;
        *(a+1) = 100;
        printf("%d\n", *a);
        printf("%d\n", *(a+1));
        printf("%d\n", *(a+2));

        */

    a = takeMemory(5);
    takeArray(a, 5);
    printArray(a, 5);

    free(a);

    return 0;
}
