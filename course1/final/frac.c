#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int32_t frac_add(int32_t *x,int32_t *y,int32_t a,int32_t b,int32_t c,int32_t d){
	if(b*d==0)return -1;
	*x=a*d+c*b;
	*y=b*d;
	if(*x==0)*y=1;
	if(*y<0)*x=-*x,*y=-*y;
	for(int i=2;i<=*y;i++)while(*x%i==0&&*y%i==0)*x/=i,*y/=i;
	return 0;
}
int32_t frac_del(int32_t *x,int32_t *y,int32_t a,int32_t b,int32_t c,int32_t d){
	if(b*d==0)return -1;
	*x=a*d-c*b;
	*y=b*d;
	if(*x==0)*y=1;
	if(*y<0)*x=-*x,*y=-*y;
	for(int i=2;i<=*y;i++)while(*x%i==0&&*y%i==0)*x/=i,*y/=i;
	return 0;
}
int32_t frac_mul(int32_t *x,int32_t *y,int32_t a,int32_t b,int32_t c,int32_t d){
	if(b*d==0)return -1;
	*x=a*c;
	*y=b*d;
	if(*x==0)*y=1;
	if(*y<0)*x=-*x,*y=-*y;
	for(int i=2;i<=*y;i++)while(*x%i==0&&*y%i==0)*x/=i,*y/=i;
	return 0;
}
int32_t frac_div(int32_t *x,int32_t *y,int32_t a,int32_t b,int32_t c,int32_t d){
	if(b*d==0||b*c==0)return -1;
	*x=a*d;
	*y=b*c;
	if(*x==0)*y=1;
	if(*y<0)*x=-*x,*y=-*y;
	for(int i=2;i<=*y;i++)while(*x%i==0&&*y%i==0)*x/=i,*y/=i;
	return 0;
}
