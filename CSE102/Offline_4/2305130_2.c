#include <stdio.h>
#include <stdlib.h>


int main()
{
    int lim = 10001;
    int* freq = calloc(lim, sizeof(int));

    int n, a;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        *(freq+a) += 1;
    }

    int max = 0;
    for (int i = 0; i < lim; i++) max = (max > *(freq+i)) ? max : *(freq+i);
    for (int i = 0; i < lim; i++)
    {
        if (*(freq+i) == max) printf("%d ", i);
    }

    return 0;
}