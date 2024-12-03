#include<stdio.h>

int main(){
    int a = 500;

    int *p;
    p = &a;

    printf("Value of P: %d\n", p);
    printf("Value of P+1: %d\n", p+1);
    printf("Value of P+2: %d\n", p+2);
    printf("Value of P-1: %d\n", p-1);

    char *q;

    char c;

    q = &a;

    *q = 'x';

    printf("Value of Q: %d\n", q);
    printf("Value of Q+1: %d\n", q+1);
    printf("Value of Q+2: %d\n", q+2);
    printf("Value of Q-1: %d\n", q-1);


    void *v;

    v = &a;

    printf("Value of V: %d\n", v);
    printf("Value of V+1: %d\n", v+1);
    printf("Value of V+2: %d\n", v+2);
    printf("Value of V-1: %d\n", v-1);

    printf("Value of A: %d\n",a);
    printf("Dereferencing P: %d\n", *p);
    printf("Dereferencing Q: %d\n", *q);
    // printf("Dereferencing V: %d", *v);
/*
    printf("Size of pointer variable: %d\n", sizeof(int*));
    printf("Size of pointer variable: %d\n", sizeof(char*));
    printf("Size of pointer variable: %d\n", sizeof(double*));
*/

    return 0;
}
