#include<stdio.h>
#include<stdlib.h>


int main()
{
    int str[100];
    int i = 0;

    gets(str);

    while(++i)
    {
        if (str[i] == 0) break;
    }

    i = i/2;

    while(i--)
    {
        str[i];
    }


    return 0;
}
