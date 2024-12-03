// 33
#include <stdio.h>
#include <time.h>
#include <math.h>

int n, k, N, D, i, j;
long long sumN, sumD;
double fraction;
int d1[4], d2[4];
int match[4][5]; // 1 --> same; 0 --> not same
int number[2][4];

int combination(int p, int q){
    int run;
    if(q-1 == k){
        N = 0;
        D = 0;
        for(int z=0; z<n; z++){
            if(!number[0][z]){
                N *= 10;
                N += d1[z];
            }
            if(!number[1][z]){
                D *= 10;
                D += d2[z];
            }
        }
        if((double)N/(double)D == fraction){
            // printf("%d %d\n", i, j);
            sumN += i;
            sumD += j;
            return 0;
        }
        return q;
    }
    for(int x=p; x<n; x++){
        if(match[x][0]){
            for(int y=1; y<=n; y++){
                if(match[x][y] && !number[1][y-1]){
                    number[1][y-1] = 1;
                    number[0][x] = 1;
                    run = combination(p+1, q+1);
                    number[1][y-1] = 0;
                    number[0][x] = 0;
                    if(run == 0)
                    return 0;
                }
            }
        }
    }
    return q;
}

int main(){
    int t, min, temp, m;
    sumN = 0;
    sumD = 0;
    scanf("%d %d", &n, &k);

    min = pow(10, n-1);
    for(i=min; i<min*10; i++){
        temp = i;
        for(int a=n-1; a>=0; a--){
            d1[a] = temp%10;
            temp = temp/10;
        }
        for(j=i+1; j<min*10; j++){
            fraction = (double)i/(double)j;
            // printf("i-%d; j-%d --- %f\n", i, j, fraction);
            temp = j;
            for(int a=n-1; a>=0; a--){
                d2[a] = temp%10;
                temp = temp/10;
            }
            m = 0;
            for(int a=0; a<n; a++){
                temp = 0;
                match[a][0] = 0;
                for(int b=0; b<n; b++){
                    if(d1[a] == d2[b] && d1[a] != 0){
                        match[a][b+1] = 1;
                        match[a][0] = 1;
                        temp = 1;
                    }
                    else
                    match[a][b+1] = 0;
                }
                if(temp)
                m++;
            }
            if(m >= k){
                combination(0, 1);
            }
        }
    }
    printf("%lld %lld\n", sumN, sumD);
    return 0;
}


/*
2,1 - 110 322
3,1 - 77262 163829
3,2 - 7429 17305
4,1 - 12999936 28131911
4,2 - 3571225 7153900
4,3 - 255983 467405
*/