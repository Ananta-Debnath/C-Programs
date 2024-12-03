#include<stdio.h>

int main()
{
    int row = 2, col= 3;
    ///int a[row][col];
    int *a;

    a = (int*)malloc(row*col*sizeof(int));

    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%d ", (a+i*col+j));
        }
        printf("\n");
    }
    free(a);
    return 0;
}
