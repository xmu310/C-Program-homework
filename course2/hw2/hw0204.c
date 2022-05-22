#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include"myfrac.h"
int main(){
	int x,n=0;
	char buf[5000],*p=buf,si[5000]={0};
	sMixedNumber s[5000]={0},tmp;
	printf("Q: ");
	scanf("%[^\n]",buf);
	if(!*p)f();
	while(*p){
		if(*p=='(')p++;
		s[n].a=strtol(p,&p,10);
		if(*p==92){p+=6,s[n].b=strtol(p,&p,10),p+=2,s[n].c=strtol(p,&p,10),p++;}else s[n].b=0,s[n].c=1;
		if(*p==')')p++;
		check(&s[n]);
		if(*p)si[n]=*p,p++;
		n++;
	}
	while(p=strpbrk(si,"*/")){
		x=p-si;
		if(*p=='*')mixed_mul(&tmp,s[x],s[x+1]);else if(s[x+1].b)mixed_div(&tmp,s[x],s[x+1]);else f();
		simp(&tmp);
		s[x]=tmp,n--;
		for(int i=x;i<n;i++)s[i+1]=s[i+2],si[i]=si[i+1];
	}
	while(*si){
		if(*si=='+')mixed_add(&tmp,s[0],s[1]);else mixed_sub(&tmp,s[0],s[1]);
		simp(&tmp);
		s[0]=tmp,n--;
		for(int i=0;i<n;i++)s[i+1]=s[i+2],si[i]=si[i+1];
	}
	s[0].a=s[0].b/s[0].c,s[0].b=abs(s[0].b%s[0].c);
	printf("A: ");
	if(!s[0].a&&!s[0].b){
		printf("0\n");
	}else{
		if(s[0].a)printf("%ld",s[0].a);
		if(s[0].b)printf("\\frac{%ld}{%ld}",s[0].b,s[0].c);
		printf("\n");
	}
	return 0;
}
