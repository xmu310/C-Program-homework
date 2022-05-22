#include<stdio.h>
int main()
{
	float v,a,t;
	printf("v_0: ");
	scanf("%f",&v);
	printf("a: ");
	scanf("%f",&a);
	printf("t: ");
	scanf("%f",&t);
	printf("--> s = %f\n",v*t+a*t*t/2);
	return 0;
}
