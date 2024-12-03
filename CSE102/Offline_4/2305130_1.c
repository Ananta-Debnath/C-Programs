#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void reverseWords(char* a, char* t)
{
    int l = strlen(a);
    int idx = 0;
    int start = 0;

    for (int i = l; i >= start; i--)
    {
        if (i == 0 || *(a+i-1) == ' ')
        {
            for (int j = i; j < l; j++, idx++)
            {
                *(t+idx) = *(a+j);
            }
            if(i != l)
            {
                *(t+idx) = ' ';
                idx++;
            }
            l = i - 1;
        }
    }
    *(t+idx-1) = 0;
}



int main()
{
    char* str = malloc(512 * sizeof(char));
    gets(str);

    int l = strlen(str);
    char* reversed = calloc((l+1), sizeof(char));

    reverseWords(str, reversed);

    printf("%s\n", reversed);

    return 0;
}