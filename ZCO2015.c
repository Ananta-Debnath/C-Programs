#include <stdio.h>

int main(){
    int n, v = 0;
    scanf("%d", &n);
    int p[n+2][2], b1[2], b2[2];

    for(int i = 0; i < n+2; i++){
        p[i][0] = 0;
        p[i][1] = 0;
    }
    p[n+1][0] = 100000;

    for(int i = 1; i <= n; i++){
        v = 0;
        scanf("%d %d", &b1[0], &b1[1]);
        if(b1[1] = 0){
            b1[1] = 500;
        }
        for(int j = 0; j <= i; j++){
            if(v == 1 || b1[0] <= p[j][0]){
                v = 1;
                for(int k = 0; k < 2; k++){
                    b2[k] = p[i][k];
                    p[i][k] = b1[k];
                    b1[k] = b2[k];
                }
            }
            else if(p[i][0] == 0 && p[i][1] == 0){
                p[i][0] = b1[0];
                p[i][1] = b1[1];
            }
        }
    }

    long long int MaxArea = 0, area;
    int maxX = 0, x, y, x1, x2;

    for(int i = 1; i < n+2; i++){
        x = p[i][0] - p[i-1][0];
        if(x > maxX){
            maxX = x;
        }
    }
    // printf("%d", maxX);
    MaxArea = 500 * maxX;
    // printf("%d", MaxArea);

    for(int i = 1; i <= n; i++){
        x = p[i][0];
        y = p[i][1];
        for(int j = i - 1; j >= 0; j--){
            if(y > p[j][1]){
                x1 = p[j][0];
                break;
            }
        }
        for(int j = i + 1; j < n; j++){
            if(y > p[j][1]){
                x2 = p[j][0];
                break;
            }
        }
        area = y * (x2 - x1);
        if(area > MaxArea){
            MaxArea = area;
        }
        // printf("%d\n", MaxArea);
    }
    
    printf("%d", MaxArea);
    
    
	return 0;
}

