#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	int64_t y[1000]={0},n=0,py;
	double t[1000]={0},ya=0,ta=0,a1=0,a2=0,a,b;
	for(int i=0;i<1000;i++){
		printf("Please enter the year: ");scanf("%ld",&y[i]);
		if(y[i]<1900&&y[i]!=-1){printf("Illegal input! (Only allowed input >= 1900.)\n");exit(0);}
		if(y[i]==-1)break;
		printf("Temperature: ");scanf("%lf",&t[i]);
		if(t[i]<-273.15){printf("Illegal input! (Only allowed input >= -273.15.)\n");exit(0);}
		ya+=y[i],ta+=t[i],a1+=y[i]*t[i],a2+=y[i]*y[i],n++;
	}
	if(n<2){printf("The amount of data is not enough to predict.\n");exit(0);}
	ya/=(double)n,ta/=(double)n,a1-=n*ya*ta,a2-=n*ya*ya,a=a1/a2,b=ta-a*ya;
	printf("Please enter the prediction year: ");scanf("%ld",&py);
	printf("Temperature: %.4lf\n",a*py+b);
	return 0;
}
