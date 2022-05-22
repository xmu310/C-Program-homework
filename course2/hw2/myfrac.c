#include<stdio.h>
#include<stdlib.h>
#include"myfrac.h"
void mixed_add(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2){(*pNumber).b=r1.b*r2.c+r2.b*r1.c,(*pNumber).c=r1.c*r2.c;}
void mixed_sub(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2){(*pNumber).b=r1.b*r2.c-r2.b*r1.c,(*pNumber).c=r1.c*r2.c;}
void mixed_mul(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2){(*pNumber).b=r1.b*r2.b,(*pNumber).c=r1.c*r2.c;}
void mixed_div(sMixedNumber *pNumber,const sMixedNumber r1,const sMixedNumber r2){(*pNumber).b=r1.b*r2.c,(*pNumber).c=r1.c*r2.b;}
void simp(sMixedNumber *p){int64_t n=2;while(n<=abs((*p).b)&&n<=abs((*p).c))if(!((*p).b%n)&&!((*p).c%n))(*p).b/=n,(*p).c/=n;else n++;}
void f(){printf("error!\n");exit(0);}
void check(sMixedNumber *p){if(!(*p).c)f();(*p).b=(*p).a*(*p).c+(*p).b*((*p).a<0?-1:1),(*p).a=0;if((*p).c<0)(*p).b*=-1,(*p).c*=-1;simp(p);}

