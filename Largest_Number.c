#include <stdio.h>

int main()
{
	float a, b, c;
	scanf("%f %f %f", &a, &b, &c);
	float x=a;
	if(x<b){
		x=b;
	}
	if(x<c){
		x=c;
	}
	printf("%f", x);
	return 0;
}