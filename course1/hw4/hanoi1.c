#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void hanoi1(int64_t m,int64_t a,int64_t b,int64_t c){
	if(m-1!=0)hanoi1(m-1,a,c,b);
	printf("move disk %ld to rod %ld\n",m,b);
	if(m-1!=0)hanoi1(m-1,c,b,a);
}
