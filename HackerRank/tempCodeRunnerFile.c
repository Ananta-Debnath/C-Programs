#include <stdio.h>

int main() 
{

    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.
    int a, b, l, t;
    l = 2*n - 1;
    for (int i = 0; i < l; i++)
    {
        a = (i < n) ? (n - i) : (i - n + 2);
        for (int j = 0; j < l; j++)
        {
            b = (j < n) ? (n - j) : (j - n + 2);
            t = (a > b) ? a : b;
            printf("%d ", t);
        }
        printf("\n");
    }
    
    return 0;
}