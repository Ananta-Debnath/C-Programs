#include <stdio.h>
#include <stdlib.h>


int* square(int x)
{
    int* result = malloc(sizeof(int));
    *result = x * x;
    return result;
}

int binary_search(int* a, int l, int t)
{
    int first=0, last=l-1, mid, index = -1;
    while(first<=last)
    {
        mid = (first + last)/2;
        if(a[mid]<t) first = mid + 1;
        else if(a[mid]>t) last = mid -1;
        else
        {
            index = mid;
            break;
        }
    }
    return index;
}

int main()
{
    int a[] = {1,4,6,9,11,13,14,16,17,18,20,22};
    int n = 12;
    int t = 17;

    int idx = binary_search(a, n, t);
    printf("%d", idx);

    return 0;
}
