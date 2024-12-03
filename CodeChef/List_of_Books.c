#include <stdio.h>

int main(){
    int b, n, r;
	scanf("%d", &b);

	int bs[b];
    for (int i = 0; i<b; i++){
        scanf("%d", &(bs[i]));
    }

    scanf("%d", &n);
    for (int i = 0; i<n; i++){
        scanf("%d", &r);
        printf("%d\n", bs[r-1]);
        for(int j = r; j<(b-i); j++){
            bs[j-1] = bs[j];
        }
    }
    return 0;
}