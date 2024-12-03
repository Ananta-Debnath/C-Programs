#include<stdio.h>

int main(){
    int *a;

    a = (int*)malloc(8);
    free(a);
    a = (int*)malloc(8);

    free(a);

    return 0;
}
