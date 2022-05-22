#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#include"myvector.h"
sVector* mems[5000]={0};
int64_t num=0;
int check(const sVector *p){return p&&((*p).type==1||(*p).type==2&&(*p).data.p.distance>=0);}
double p_d(const sVector *p){sVector s=*p;return s.type==1?hypot(s.data.c.x,s.data.c.y):s.data.c.x;}
double p_a(const sVector *p){
	sVector s=*p;
	if(s.type==2){
		while(s.data.p.angle>=2*acos(-1))s.data.p.angle-=2*acos(-1);
		while(s.data.p.angle<0)s.data.p.angle+=2*acos(-1);
		return s.data.p.angle;
	}
	if(!p_d(&s))return 0;
	double n=acos(s.data.c.x/p_d(&s));
	return s.data.c.y>=0?n:2*acos(-1)-n;
}
double c_x(const sVector *p){sVector s=*p;return s.type==2?s.data.p.distance*cos(s.data.p.angle):s.data.c.x;}
double c_y(const sVector *p){sVector s=*p;return s.type==2?s.data.p.distance*sin(s.data.p.angle):s.data.c.y;}
sVector *myvector_init(){sVector* p=calloc(1,sizeof(sVector));num++;mems[num-1]=p;return p;}
int myvector_set(sVector *pVector,uint8_t type,double a,double b){
	if(!pVector||type!=1&&type!=2||type==2&&a<0)return -1;
	int64_t x=0;
	for(int i=0;i<num;i++)if(pVector==mems[i])x=1;
	if(!x)return -1;
	(*pVector).type=type,(*pVector).data.c.x=a,(*pVector).data.c.y=b;
	return 0;
}
int myvector_print(const sVector *pVector,uint8_t type){
	if(!check(pVector)||type!=1&&type!=2)return -1;
	if(type==1)printf("(%lf,%lf)\n",c_x(pVector),c_y(pVector));else printf("(%lf,%lf-pi)\n",p_d(pVector),p_a(pVector)/acos(-1));
	return 0;
}
int myvector_add(sVector *pA,const sVector *pB,const sVector *pC){
	if(!pA||!check(pB)||!check(pC))return -1;
	int64_t x=0;
	for(int i=0;i<num;i++)if(pA==mems[i])x=1;
	if(!x)return -1;
	sVector s=*pA;
	s.type=1,s.data.c.x=c_x(pB)+c_x(pC),s.data.c.y=c_y(pB)+c_y(pC),(*pA).type=(*pB).type;
	if((*pB).type==2)(*pA).type=2,(*pA).data.p.distance=p_d(&s),(*pA).data.p.angle=p_a(&s);else *pA=s;
	return 0;
}
int myvector_inner_product(double *pA,const sVector *pB,const sVector *pC){
	if(!pA||!check(pB)||!check(pC))return -1;
	*pA=c_x(pB)*c_x(pC)+c_y(pB)*c_y(pC);
	return 0;
}
int myvector_area(double *pArea,const sVector *pB,const sVector *pC){
	if(!pArea||!check(pB)||!check(pC))return -1;
	*pArea=fabs(c_x(pB)*c_y(pC)-c_x(pC)*c_y(pB));
	return 0;
}
int myvector_cvp(double *pX,double *pY,const double *pTx,const double *pTy,const sVector *pA,const sVector *pB){
	if(!pX||!pY||!pTx||!pTy||!check(pA)||!check(pB))return -1;
	double tx=*pTx,ty=*pTy,a=0,b=0,ta=a,tb=b,x1=c_x(pA),x2=c_x(pB),y1=c_y(pA),y2=c_y(pB);
	do{
		ta=a,tb=b;
		while(hypot((a+1)*x1+b*x2-tx,(a+1)*y1+b*y2-ty)<hypot(a*x1+b*x2-tx,a*y1+b*y2-ty))a++;
		while(hypot((a-1)*x1+b*x2-tx,(a-1)*y1+b*y2-ty)<hypot(a*x1+b*x2-tx,a*y1+b*y2-ty))a--;
		while(hypot(a*x1+(b+1)*x2-tx,a*y1+(b+1)*y2-ty)<hypot(a*x1+b*x2-tx,a*y1+b*y2-ty))b++;
		while(hypot(a*x1+(b-1)*x2-tx,a*y1+(b-1)*y2-ty)<hypot(a*x1+b*x2-tx,a*y1+b*y2-ty))b--;
	}while(a!=ta||b!=tb);
	*pX=a*x1+b*x2,*pY=a*y1+b*y2;
	return 0;
}
