#include <stdio.h>

/*
// Problem 1 (With tmp)
int main()
{
    int a, b, c, tmp;
    scanf("%d%d%d", &a, &b, &c);

    tmp = c;
    c = b;
    b = a;
    a = tmp;

    printf("%d %d %d\n", a, b, c);

    return 0;
}
*/


/*
// Problem 1 (Without tmp)
int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    c = a + b + c;
    a = c - (a + b);
    b = c - (a + b);
    c = c - (a + b);

    printf("%d %d %d\n", a, b, c);

    return 0;
}
*/


/**/
// Problem 2
int main()
{
    char c;
    scanf("%c", &c);

    c -= 'a';
    c += 1;
    c = c % 26;
    c += 'a';

    printf("%c\n", c);

    return 0;
}
