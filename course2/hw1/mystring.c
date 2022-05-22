#include<stdio.h>
size_t mystrlen(const char *s){for(size_t i=0;;i++)if(!*(s+i))return i;}
char *mystrchr_core(const char *s,int c,int flag){
	for(size_t i=0;i<mystrlen(s)+1;i++)if(*(flag?s+i:s+mystrlen(s)-i)==c)return (char*)(flag?s+i:s+mystrlen(s)-i);
	return NULL;
}
size_t mystrspn_core(const char *s,const char *list,int flag){
	for(size_t re=0,check=1;;re++,check=1){
		for(size_t i=0;i<mystrlen(list);i++)check*=*(s+re)!=*(list+i);
		if((flag?check:!check)||re+1>mystrlen(s))return re;
	}
}
char *mystrchr(const char *s,int c){return mystrchr_core(s,c,1);}
char *mystrrchr(const char *s,int c){return mystrchr_core(s,c,0);}
size_t mystrspn(const char *s,const char *accept){return mystrspn_core(s,accept,1);}
size_t mystrcspn(const char *s,const char *reject){return mystrspn_core(s,reject,0);}
char *mystrpbrk(const char *s,const char *accept){
	char *re=NULL,*p;
	for(size_t i=0;i<mystrlen(accept);i++){p=mystrchr(s,*(accept+i));if(!re||re&&p&&p<re)re=p;}
	return re;
}
char *mystrstr(const char *haystack,const char *needle){
	for(size_t i=0,check=1;i<mystrlen(haystack)+1;i++,check=1){
		for(size_t j=0;j<mystrlen(needle);j++)check*=*(haystack+i+j)==*(needle+j);
		if(check)return (char*)(haystack+i);
	}
	return NULL;
}
char *mystrtok(char *str,const char *delim){
	static char *cur,*next;
	cur=(str?str:next),cur+=mystrspn(cur,delim),next=cur+mystrcspn(cur,delim),*next=0,next++;
	return *cur?cur:NULL;
}
#include<limits.h>
long int myctol_core(int c){if(c>='0'&&c<='9')return c-'0';int t=c&0xdf;if(t>='A'&&t<='Z')return t-'A'+10;return -1;}
long int myctol(int c,long int base){long int re=myctol_core(c);return re>=0&&re<base?re:-1;}
long int mystrtol(const char *nptr,char **endptr,int base){
	if(base>36||base<0||base==1){*endptr=NULL;return 0;}
	const char *p=nptr+mystrspn(nptr," \f\n\r\t\v");
	long int check=0,re=0,tmp=0,sign=*p=='-'?-1:1,b=base,digit,overflow=0;
	p+=*p=='+'||*p=='-'?1:0;
	if((!b||b==16)&&*p=='0'&&(*(p+1)&0xdf)=='X')if(myctol(*(p+2),16)+1)b=16,p+=2;else{*endptr=(char*)p+1;return 0;}
	if(!b&&*p=='0')if(myctol(*(p+1),8)+1)b=8,p+=1;else{*endptr=(char*)p+1;return 0;}
	if(!b)b=10;
	while((digit=myctol(*p,b))+1)check=1,tmp=re*b+digit,p++,overflow=(tmp-digit)/b!=re?1:overflow,re=tmp;
	if(overflow)re=sign>0?LONG_MAX:LONG_MIN;else re*=sign;
	if(check){*endptr=(char*)p;return re;}else{*endptr=(char*)nptr;return 0;}
}
