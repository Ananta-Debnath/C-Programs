#include<stdio.h>

int main()
{
    int n = 0;
    printf("Number of elements: ");
    scanf("%d", &n);
    int a[n];
    printf("List: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("Initial order: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    int m = 0;
    printf("Number of instructions: ");
    scanf("%d", &m);

    int k;
    for (int i = 0; i < m; i++)
    {
        printf("Instruction: ");
        scanf("%d", &k);
        if (k < 0) k += n;
        
        int tmp;
        for (int j = 0; j < n/2; j++)
        {
            tmp = a[j];
            a[j] = a[n-j-1];
            a[n-j-1] = tmp;
        }
        for (int j = 0; j < k/2; j++)
        {
            tmp = a[j];
            a[j] = a[k-j-1];
            a[k-j-1] = tmp;
        }
        for (int j = k; j < (n+k)/2; j++)
        {
            tmp = a[j];
            a[j] = a[n-j+k-1];
            a[n-j+k-1] = tmp;
        }

        printf("After instruction: ");
        for (int j = 0; j < n; j++) printf("%d ", a[j]);
        printf("\n");
    }

    int max = a[0], max_idx = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
            max_idx = i+1;
        }
    }

    printf("Winner: Child %d\n", max_idx);

    return 0;
}



/*
5
1 2 3 4 5
3
2 -1 3
*/