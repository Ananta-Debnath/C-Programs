#include <stdio.h>
#include <limits.h>

int main()
{
    int n, a, min, max;
    int sum = 0, even = 0, odd = 0;
    printf("How many numbers do you want to enter? ");
    scanf("%d", &n);

    printf("Enter %d numbers: ", n);
    scanf("%d", &a);
    max = min = a;
    (a % 2) ? odd++ : even++;
    sum += a;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &a);
        max = (a > max) ? a : max;
        min = (a < min) ? a : min;
        (a % 2) ? odd++ : even++;
        sum += a;
    }

    float avg = sum/(float)n;

    printf("\nMinimum Number: %d\n", min);
    printf("Maximum Number: %d\n", max);
    printf("Sum of all Numbers: %d\n", sum);
    printf("Average: %f\n", avg);
    printf("Even Number Count: %d\n", even);
    printf("Odd Number Count: %d\n", odd);

    return 0;
}