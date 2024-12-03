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
        k = k % n;

        for (int j = 0; j < k; j++)
        {
            int tmp = a[n-1];
            for (int x = n-1; x > 0; x--) a[x] = a[x-1];
            a[0] = tmp;
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