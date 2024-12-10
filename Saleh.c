#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    char* str = malloc(1024 * sizeof(char));
    gets(str);

    int start = 0, l = 0, idx = 0;
    int n = strlen(str);

    for (int i = 0; i <= n; i++)
    {
        if (str[i] == ' ' || str[i] == 0)
        {
            if (l < (i - start))
            {
                l = i - start;
                idx = start;
            }
            str[i] = 0;
            start = i + 1;
        }
    }

    char* ans = malloc((l+1) * sizeof(char));
    for(int i = 0; i <= l; i++) ans[i] = str[idx + i];

    printf("%s", ans);
    free(str);
}