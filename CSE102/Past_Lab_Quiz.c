#include <stdio.h>
#include <stdlib.h>




/*
int leapYear(int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return 1;
    else return 0;
}

int leapYearTernary(int year)
{
    int leap = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? 1 : 0;
    return leap;
}

int main()
{
    int year;
    scanf("%d", &year);
    int leap = leapYearTernary(year);
    printf("%d\n", leap);
    main();

    return 0;
}
*/



/*
double square(double x)
{
    return x * x;
}

double cube(double x)
{
    return x * x * x;
}

double average(double *numbers, int count, double (*fn)(double))
{
    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += fn(numbers[i]);
    }
    return sum / count;
}

double *take_input(int count)
{
    double *numbers = (double *)calloc(count, sizeof(double));
    double *initial = numbers;
    while (count--)
    {
        scanf("%lf", numbers);
        numbers++;
    }
    return initial;
}

int main()
{
    // complete the main function to perform the mentioned tasks.
    int count;
    scanf("%d", &count);
    double* numbers = take_input(count);

    double sqAvg = average(numbers, count, square);
    double cubeAvg = average(numbers, count, cube);

    printf("Square Average: %lf\n", sqAvg);
    printf("Cube Average: %lf\n", cubeAvg);

    free(numbers);

    return 0;
}
*/



/*
void quiz(int n)
{
    if (n > 0)
    {
        printf("%d ", n);
        quiz(n - 1);
        printf("%d ", n);
        quiz(n - 2);
        printf("%d ", n);
    }
}

// write your answer in the following line
// 3 2 1 1 1 2 2 3 1 1 1 3
// 3 2 1 1 1 2 2 3 1 1 1 3

int main()
{
    quiz(3);
    return 0;
}
*/



/*
int main()
{
    int unit = 0;
    scanf("%d", &unit);
    int n = unit;
    int slab = (unit > 75) + (unit > 200) + (unit > 400) + (unit > 600);
    printf("Slab: %d\n", slab);

    double bill = 0;
    switch (slab)
    {
    case 4:
        bill += (n-600) * 9.98;
        n = 600;

    case 3:
        bill += (n-400) * 8.7;
        n = 400;
    
    case 2:
        bill += (n-200) * 5.36;
        n = 200;

    case 1:
        bill += (n-75) * 5.14;
        n = 75;

    case 0:
        bill += n * 3.8;
        n = 0;
        break;

    default:
        break;
    }

    printf("Bill: %lf", bill);

    return 0;
}
*/



/*
int main()
{
    int a = 10, b = 5;
    if ((a++ > 5 || b++ > 10) && (++a <= 10 || ++b <= 5))
    {
        printf("True");
    }
    else
    {
        printf("False");
    }
    printf("\n%d %d", a, b);
    return 0;
}
// write your answer in the following line
// False
// 12 6
*/



/*
int factorial(int n)
{
    if (n == 1)
        return 1;
    return n * factorial(n - 1);
}
// write your corrected code below

int main()
{
    int n = factorial(5);
    printf("%d\n", n);
}
*/



/*
void main()
{
    int **p;
    p = (int**)malloc(4 * sizeof(int *)); //
    if (p == NULL) //
        return;

    int i; //
    for (i = 0; i < 4; i++) //
        p[i] = (int *)malloc(5 * sizeof(int));
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++) //
        {
            scanf("%d", *(p + i) + j);
        }
    }
    int sum = 0;
    for (i = 0; i < 5; i++)
        sum += *(*(p + 2) + i);
    for (i = 0; i < 4; i++)
        sum += *(*(p + i) + 3);
    printf("\n%d", sum);
    for (i = 0; i < 4; i++)
        free(*(p + i)); //
    free(p);
}
*/



/*
int main()
{
    int n;
    scanf("%d", &n);

    int sum = 0;
    for (int i = 1; i <= n; i++) sum += i*i;
    printf("Sum = %d\n", sum);

    sum = 0;
    int t = 1;
    while (t <= n)
    {
        sum += t*t;
        t++;
    }
    printf("Sum = %d\n", sum);

    sum = 0;
    t = 0;
    do
    {
        sum += t*t;
        t++;
    } while (t <= n);
    printf("Sum = %d\n", sum);
}
*/