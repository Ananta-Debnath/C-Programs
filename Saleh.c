#include <stdio.h>
#include <stdlib.h>


int* square(int x)
{
    int* result = malloc(sizeof(int));
    *result = x * x;
    return result;
}

int main()
{
    int a = 10;
    int *p;
    
    p = square(a);
    
    printf("%d", *p);

    return 0;
}
