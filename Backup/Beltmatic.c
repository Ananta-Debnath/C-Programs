#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct equation
{
    int num[3];
    struct equation* numEq[3];
    char operator[3];
}
equation;

int start[50];
int limit;
int act_limit[] = {1, 1};
int minSteps = 0;
double (*rounded[2])(double);

int action_count;
equation* (*action[2])(int, int, int);


int getStartingNumbers()
{
    FILE *fptr;
    fptr = fopen("Beltmatic.txt", "r");
    if (fptr == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    start[0] = 0;
    int a;
    limit = 1;

    int size = 5;
    char line[size];
    while(1)
    {
        fgets(line, size, fptr);
        a = atoi(line);
        if (a == start[limit-1]) break;
        start[limit] = a;
        limit++;
    }

    return 0;
}


int print_equation(equation* eq)
{
    printf("(");
    for (int i = 0; i < 3; i++)
    {
        if (eq->numEq[i] == NULL) printf("%d", eq->num[i]);
        else print_equation(eq->numEq[i]);
        printf("%c", eq->operator[i]);
    }
    printf(")");
}

int free_equation(equation* eq)
{
    for (int i = 0; i < 3; i++)
    {
        if (eq->numEq[i] != NULL)
        {
            free_equation(eq->numEq[i]);
        }
    }
    free(eq);
}

char find_sign(equation* eq)
{
    if (eq->num[2] < 0)
    {
        eq->num[2] *= -1;
        return '-';
    }
    else return '+';
}

int __multiple(int n, int a, int* extra)
{
    double b_f = n / (double)a;
    int b = round(b_f);

    int c = a * b;

    *extra = n - c;
    return b;
}

int __exponent(int n, int a, int* extra)
{
    double b_f = log2f(n) / log2f(a);
    int b = round(b_f);

    int c = 1;
    for (int i = 0; i < b; i++) c *= a;

    *extra = n - c;
    return b;
}


equation* multiple(int n, int a, int p)
{
    equation* eq = malloc(sizeof(equation));
    if (eq == NULL)
    {
        printf("Memory allocation error in exponent\n");
        return NULL;
    }

    eq->num[0] = a;
    eq->operator[0] = '*';

    double b_f = n / (double)a;
    eq->num[1] = rounded[p](b_f);

    eq->num[2] = eq->num[0] * eq->num[1];

    eq->num[2] = n - eq->num[2];
    eq->operator[1] = find_sign(eq);
    return eq;
}

equation* exponent(int n, int a, int p)
{
    equation* eq = malloc(sizeof(equation));
    if (eq == NULL)
    {
        printf("Memory allocation error in exponent\n");
        return NULL;
    }

    eq->num[0] = a;
    eq->operator[0] = '^';

    double b_f = log2f(n) / log2f(a);
    eq->num[1] = rounded[p](b_f);

    eq->num[2] = 1;
    for (int i = 0; i < eq->num[1]; i++) eq->num[2] *= a;

    eq->num[2] = n - eq->num[2];
    eq->operator[1] = find_sign(eq);
    return eq;
}

equation* find_eq(int n, int *step)  // 7 ^ 3 + 9 = 352; 3 ^ 4 + 7 = 88;
{
    for (int i = 0; i < limit; i++)
    {
        if (n == start[i]) return NULL;
    }

    int check;
    int startStep = *step;
    equation* mainEq = NULL;
    equation* eq;

    for (int k = 0; k < action_count; k++)
    {
        int a = 2;
        do
        {
            for (int i = 0; i < 2; i++)
            {
                *step = startStep;
                if(*step > minSteps - 2)
                {
                    *step += 2;
                    return mainEq;
                }

                eq = action[k](n, a, i);
                check = eq->num[1];
                eq->operator[2] = 0;
                if (eq->num[1] > 1) *step += 1;
                if (eq->num[2] != 0) *step += 1;

                for (int j = 0; j < 3; j++)
                {
                    eq->numEq[j] = find_eq(eq->num[j], step);
                }

                ///*
                printf("%d = ", n);
                print_equation(eq);
                printf(" -- step = %d, min = %d\n", *step, minSteps);
                //*/

                if (*step <= minSteps)
                {
                    if (mainEq != NULL) free_equation(mainEq);
                    // minSteps = *step;
                    mainEq = eq;
                    return mainEq;
                }
                else
                {
                    free_equation(eq);
                }
                // *step = minSteps;
            }

            act_limit[1] = a;
            a++;
        }
        while (check > act_limit[k]);
    }
    return mainEq;
}

int main()
{
    rounded[0] = ceil;
    rounded[1] = floor;

    action[0] = exponent;
    action[1] = multiple;
    action_count = sizeof(action) / sizeof(equation*);

    getStartingNumbers();

    int n;
    int step;
    equation* mainEq;

    while(1)
    {
        printf("Number: ");
        scanf("%d", &n);

        mainEq = NULL;
        while (mainEq == NULL)
        {
            step = 0;
            minSteps += 1;
            mainEq = find_eq(n, &step);
        }
        
        // for (int i = 0; i < 3; i++) printf("%d\n", mainEq->num[i]);
        printf("\n\n\n%d = ", n);
        print_equation(mainEq);
        printf("\n");

        free_equation(mainEq);
    }
    
    /*
    int y = 3;
    int operation[limit - 1][y];

    for(int i = 0; i < action_count; i++)
    {
        for (int j = 2; j <= limit; j++)
        {
            operation[j-2][0] = j;
            operation[j-2][1] = action[i](n, j, &operation[j-2][2]);
        }
        
        for (int j = 0; j < limit - 1; j++)
        {
            printf("((%d %c %d) + %d)\n", operation[j][0], sign[i], operation[j][1], operation[j][2]);
        }
        printf("\n");
    }
    */
}


/*
23986 = (11*(3^7-6)-5)))

9954 = (6^5+(3^7-9))

3788 = (2^11+(12^3+12))
*/