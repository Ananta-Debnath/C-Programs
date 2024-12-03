#include<stdio.h>

void swap(int *p, int *q){
    int t = *p;
    *p = *q;
    *q = t;
}

int* takeArray(int n){
    int a[n];
    int i;
    for(i = 0;i<n;i++){
        scanf("%d", &a[i]);
    }
    return a;
}

int main(){
    int n = 4;

    int *arr = takeArray(n);

    for(int i=0;i<n;i++){
        printf("%d\n", arr[i]);
    }
    return 0;
}
