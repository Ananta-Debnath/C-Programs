#include <stdio.h>

int main()
{
    int n = 0;
    printf("Number of elements: ");
    scanf("%d", n);
    int a[n];
    printf("List: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int l = 0;
    int p = 0, x, y;
    for (int i = 0; (i+l) < n; i++)
    {
        for (int j = i+l+1; j < n; j++)
        {
            x = i;
            y = j;
            while (a[x] == a[y] && x < y) 
                x++, y--;
            if (x >= y) p = i, l = j-i;
        }
    }

    for (int i = p; i <= p+l; i++) printf("%d, ", a[i]);

    return 0;
}