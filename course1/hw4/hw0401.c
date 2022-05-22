#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"k.h"
int main(){
	int64_t n;
	printf("Please enter n (1-100, n must be odd): ");
	scanf("%ld",&n);
	if(n<1||n>99||n%2==0||n/2>49){printf("Error!\n");exit(0);}
	k(n);
	return 0;
}
