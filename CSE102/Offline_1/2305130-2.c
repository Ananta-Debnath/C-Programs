#include <stdio.h>

int main()
{
    int n;
    printf("Input: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = n-i; j <= n; j++)
        {
            printf("%d", j%2);
        }
        printf("\n");
    }

    return 0;
}