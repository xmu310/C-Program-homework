#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"hanoi2.h"
int main(){
	int64_t n;
	printf("Please enter the disk number (2-20): ");
	scanf("%ld",&n);
	if(n<2||n>20){printf("Error!\n");exit(0);}
	hanoi2(n);
	return 0;
}
