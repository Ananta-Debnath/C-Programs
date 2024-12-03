#include<stdio.h>

int main()
{
    int n = 0;
    printf("Number of elements: ");
    scanf("%d", &n);
    int a[n], b[n];
    printf("List-a: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("List-b: ");
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int s = n;
        // Find a[i] in b;
        for (int j = 0; j < n; j++)
        {
            if (a[i] == b[j])
            {
                s = j + 1;
                break;
            }
        }

        for (int k = i+1; k < n; k++)
        {
            for (int j = s; j < n; j++)
            {
                if (a[k] == b[j])
                {
                    ans++;
                    break;
                }
            }
        }
    }
    printf("%d\n", ans);


    return 0;
}