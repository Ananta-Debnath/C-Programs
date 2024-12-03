#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m=0, w, x=0, y=0;
    scanf("%i", &n);
    for(int i = 0; i<n;i++)
    {
        int a, b, c;
        scanf("%i %i", &a, &b);
        x += a;
        y += b;
        c = abs(x-y);
        if(c > m){
            m = c;
            if(x > y){
                w = 1;
            }
            else{
                w = 2;
            }
        }
    }
    printf("%i %i", w, m);
    return 0;
}