#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	int64_t n;
	long double e;
	printf("Please enter n: ");scanf("%ld",&n);
	if(n<2){printf("n cannot be less than 2.\n");exit(0);}
	e=1/(1/((long double)n*2)+1)+1;
	for(int64_t i=n-1;i>=2;i--)e=1/(1/(1/e+i*2)+1)+1;
	e=1/(1/(1/e+2)+1)+2;
	printf("Answer: %.19Lf\n",e);
	return 0;
}
