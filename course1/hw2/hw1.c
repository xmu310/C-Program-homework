#include<stdio.h>
#include<stdint.h>
int main(){
	int64_t a,b,c,d;
	printf("Please enter a quadratic polynomial (a,b,c): ");
	scanf("%ld,%ld,%ld",&a,&b,&c);
	d=b*b-4*a*c;
	if(d>0){
		printf("Two distinct real roots.\n");
	}else if(d==0){
		printf("One real root.\n");
	}else{
		printf("No real roots.\n");
	}
	return 0;
}
