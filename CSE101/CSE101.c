#include<stdio.h>

int main()
{
    int a, b, c, d, tmp;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if(b>=a && b>=c && b>=d)
    {
        tmp = a;
        a = b;
        b = tmp;
    }
    else if(c>=a && c>=b && c>=d)
    {
        tmp = a;
        a = c;
        c = tmp;
    }
    else if(d>=a && d>=b && d>=c)
    {
        tmp = a;
        a = d;
        d = tmp;
    }

    if(c>=b && c>=d)
    {
        tmp = b;
        b = c;
        c = tmp;
    }
    else if(d>=b && d>=c)
    {
        tmp = b;
        b = d;
        d = tmp;
    }

    if(d>c)
    {
        tmp = c;
        c = d;
        d = tmp;
    }

    printf("%d\t%d\t%d\t%d\t", d, c, b, a);

    return 0;
}