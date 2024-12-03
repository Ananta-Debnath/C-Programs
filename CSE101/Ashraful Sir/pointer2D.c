#include<stdio.h>

int ** init2DMemory(int row, int col)
{
    int **a;
    a = (int**)malloc(row*sizeof(int*));
    int i;
    for(i=0; i<row; i++)
    {
        *(a+i) = (int*) malloc(col*sizeof(int));
    }
    return a;
}

void free2DMemory(int **a, int row, int col)
{
    int i;
    for(i=0; i<row; i++)
    {
        free(*(a+i));
    }
    free(a);
}

void take2DArray(int **a, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            scanf("%d", *(a+i)+j);
        }
    }
}

void print2DArray(int **a, int row, int col)
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%d ", *(*(a+i)+j));
        }
        printf("\n");
    }
}

int main()
{
    int **a;
    a = init2DMemory(3, 2);
    take2DArray(a, 2, 3);
    /// computation
    print2DArray(a, 2, 3);
    /// computation
    free2DMemory(a, 2, 3);

    return 0;
}
