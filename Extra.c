#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int main(){
    clock_t start1, end;
    double cpu_time_used;
    start1 = clock();



    int a = 0xA34D23;
    printf("%d\n", a);
    printf("%X\n", a);






    end = clock();
    cpu_time_used = ((double) (end - start1)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);
    return 0;
}