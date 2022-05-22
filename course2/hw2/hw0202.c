#include<stdio.h>
#include<stdint.h>
int main(){
	union{double lf;uint64_t d;}n;
	printf("Please enter a floating-point number (double precision): ");
	scanf("%lf",&n.lf);
	printf("Sign: %01ld\nExponent: ",n.d>>63&1);
	for(int i=0;i<11;i++)printf("%01lu",n.d>>62-i&1);
	printf("\nFraction: ");
	for(int i=0;i<52;i++)printf("%01lu",n.d>>51-i&1);
	printf("\n%lf = (-1)^%01lu * (1",n.lf,n.d>>63&1);
	for(int i=0;i<52;i++)if(n.d>>51-i&1)printf(" + 2^-%d",i+1);
	printf(") * 2^(%lu-1023)\n",n.d>>52&0x7FF);
	return 0;
}
