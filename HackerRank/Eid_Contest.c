#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int t;
    char c;
    int letters[2]['z'+1];

    scanf("%d", &t);
    while(t--)
    {
        int n, tmp, min = INT_MAX;

        for(int i = 'a'; i <= 'z'; i++)
        {
            letters[0][i] = 0;
            letters[1][i] = 0;
        }

        for(int i = 0; i < 2; i++)
        {
            scanf("%d", &n);
            // getchar();
            n++;
            while(n--)
            {
                scanf("%c", &c);
                letters[i][c] += 1;
            }
            // getchar();
        }

        for (int i = 'a'; i <= 'z'; i++)
        {
            if (letters[1][i] != 0)
            {
                tmp = letters[0][i]/letters[1][i];
                if(tmp < min) min = tmp;
            }
        }

        printf("%d\n", min);
    }
    
    return 0;
}