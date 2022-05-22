#include<stdio.h>
int main()
{
	int a,b;
	printf("Please enter the first  number: ");
	scanf("%d",&a);
	printf("Please enter the second number: ");
	scanf("%d",&b);
	int c=a+b;
	printf("   %d %d %d\n",a/100,a%100/10,a%10);
	printf("+) %d %d %d\n",b/100,b%100/10,b%10);
	printf("--------\n");
	if(c/1000==0)
	{
		printf("   %d %d %d\n",c/100,c%100/10,c%10);
	}
	else
	{
		printf(" %d %d %d %d\n",c/1000,c%1000/100,c%100/10,c%10);
	}
	return 0;
}
