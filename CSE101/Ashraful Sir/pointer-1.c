#include<stdio.h>

int main(){
    int a = 50;

    printf("Value of A = %d\n", a);
    printf("Address of A = %p\n", &a);

    int *p;

    /// printf("Size of pointer variable: %d", sizeof(int*));

    p = &a;

    printf("Value of A: %d\n", *p);
    printf("Address of P: %p\n", &p);
    printf("Address of A: %p\n", p);

    return 0;
}
