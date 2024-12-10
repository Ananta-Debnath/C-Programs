#include<stdio.h>
#include<stdlib.h>


int main()
{
    int r, c;
    scanf("%d %d", &r, &c);
    
    int** a = malloc(r * sizeof(int*));
    int* sum = calloc(r , sizeof(int*));
    for (int i = 0; i < r; i++) *(a+i) = malloc(c * sizeof(int));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            scanf("%d", *(a+i)+j);
            *(sum + i) += *(*(a+i)+j);
        }
    }

    int check;
    scanf("%d", &check);

    int count = 0;
    for (int i = 0; i < r; i++)
    {
        if (*(sum+i) <= check) count++;
    }

    int** ans = malloc(count * sizeof(int*));
    int idx = 0;
    for (int i = 0; i < r; i++)
    {
        if (*(sum+i) > check) free(*(a+i));
        else
        {
            *(ans+idx) = *(a+i);
            idx++;
        }
    }

    free(a);
    free(sum);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ", *(*(ans+i)+j));
        }
        printf("\n");
    }

    for (int i = 0; i < count; i++) free(*(ans+i));
    free(ans);

    return 0;
}