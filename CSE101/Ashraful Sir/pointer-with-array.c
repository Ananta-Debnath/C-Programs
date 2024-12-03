#include<stdio.h>

int main(){
    int a[5] = {5, 8, 6, 2, 9};

    ///int *p = {5, 8, 6, 2, 9};

    /// p =  a;
    //p = &a;

    int *p;
    p = &a;
/*(garbage adress diye program milano zabe na)
    for(int i=0;i<5;i++){
        scanf("%d", p+i);
    }

    for(int i=0;i<5;i++){
        printf("%d\n", *(p+i));
    }
*/

    printf("P + 2: %d\n", p+2);
    printf("*(P + 2): %d\n", *(p+2));
    printf("*P + 2: %d\n", *p+2);

/*
    printf("&a[2]: %d\n", &a[2]);
    printf("a[2]: %d\n", a[2]);


    printf("a: %d\n", a);
    printf("&a: %d\n", &a);

*/


    return 0;
}
