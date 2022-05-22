#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void f(char* s){
	printf("%s",s);
	exit(0);
}
int main(){
	int64_t w,l,t;
	double r[3][4]={{3.4,3.8,4.2,4.6},{1.4,2.0,2.3,2.6},{1.1,1.2,1.5,2.0}},d=1;
	printf("Word Count\n  Please enter the word count : ");
	scanf("%ld",&w);
	if(w<0)f("The input can not be smaller than zero.\n");
	printf("Service Level\n  1) Advanced service\n  2) Standard service\n  3) Basic service\n  Your choice : ");
	scanf("%ld",&l);
	if(l<1||l>3)f("The input is illegal.(Only allow 1 to 3)\n");
	if(l==1&&w>=2000)d=0.75;
	if(l==2&&w>=6000)d=0.9;
	if(l==3&&w>=6000)d=0.95;
	printf("Delivery Time\n  1) Economic\n  2) Standard\n  3) Fast\n  4) Deadline\n  Your choice : ");
	scanf("%ld",&t);
	if(t<1||t>4)f("The input is illegal.(Only allow 1 to 4)\n");
	printf("Proofreading fee --> %ld\n",(int64_t)(w*r[l-1][t-1]*d));
	return 0;
}
