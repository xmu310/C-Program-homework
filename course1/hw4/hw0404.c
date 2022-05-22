#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"er.h"
int main(){
	int64_t r,n;
	printf("Please enter the resistance (1-100): ");
	scanf("%ld",&r);
	if(r<1||r>100){printf("Error!\n");exit(0);}
	printf("Please enter n (1-100): ");
	scanf("%ld",&n);
	if(n<1||n>100){printf("Error!\n");exit(0);}
	printf("Ans: %lf\n",er(r,n));
	return 0;
}
