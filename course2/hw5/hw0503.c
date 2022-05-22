#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
#define f(x) do{printf(x);return 0;}while(0)
#define fch6(x) do{u24.s.c##x=fch(u24.s.c##x,6);}while(0)
#define fchk(x) do{\
	check=0;\
	for(int i=0;i<64;i++)if(c32[x]==code[i]){u24.s.c##x=i,check=1;break;}\
	if(check==0&&c32[x]!='=')f("Not base64!\n");\
	fch6(x);\
}while(0)
#define eq(cond1,cond2,x) do{if(c32[0]!='='&&c32[1]!='='&&c32[2]cond1'='&&c32[3]cond2'=')count=x;}while(0)
#define save() do{fclose(ifp);fclose(ofp);return 0;}while(0)
uint8_t fch(uint8_t c,int len){uint8_t re=0;for(int i=0;i<len;i++){re=(re<<1)+(c&1),c>>=1;}return re;}
int main(int argc,char *argv[]){
	FILE *ifp,*ofp;
	int32_t eopt=0,dopt=0,oopt=0,count,check;
	char c,*iname=NULL,*oname=NULL,code[64]={0},c32[4];
	for(int i=0;i<26;i++)code[i]='A'+i;
	for(int i=0;i<26;i++)code[26+i]='a'+i;
	for(int i=0;i<10;i++)code[52+i]='0'+i;
	code[62]='+',code[63]='/';
	union{struct{uint8_t c0:6;uint8_t c1:6;uint8_t c2:6;uint8_t c3:6;}__attribute__((packed))s;char arr[3];}u24;
	struct option lopt[]={
		{"enc",1,0,'e'},
		{"dec",1,0,'d'},
		{"output",1,0,'o'},
		{0,0,0,0}
	};
	while((c=getopt_long(argc,argv,"e:d:o:",lopt,0))!=-1){
		if(c=='e'&&!dopt){eopt=1;iname=strdup(optarg);continue;}
		if(c=='d'&&!eopt){dopt=1;iname=strdup(optarg);continue;}
		if(c=='o'){oopt=1;oname=strdup(optarg);continue;}
		if(c!=0)f("Syntax error!\n");
	}
	if(optind<argc||!iname||!oname)f("Syntax error!\n");
	ifp=fopen(iname,"r");
	ofp=fopen(oname,"w+");
	if(!ifp||!ofp)f("Open failed!\n");
	while(eopt){
		memset(&u24,0,3);
		if(!(count=fread(&u24,1,3,ifp)))break;
		for(int i=0;i<3;i++)u24.arr[i]=fch(u24.arr[i],8);
		fch6(0);fch6(1);fch6(2);fch6(3);
		putc(code[u24.s.c0],ofp);
		putc(code[u24.s.c1],ofp);
		putc(count>1?code[u24.s.c2]:'=',ofp);
		putc(count>2?code[u24.s.c3]:'=',ofp);
	}
	while(dopt){
		for(int i=0;i<4;i++){
			while(1){
				c32[i]=getc(ifp);
				if(feof(ifp))if(i)f("Wrong word number!\n");else save();
				if(c32[i]!='\n')break;
			}
		}
		fchk(0);fchk(1);fchk(2);fchk(3);
		for(int i=0;i<3;i++)u24.arr[i]=fch(u24.arr[i],8);
		count=0;eq(!=,!=,3);eq(!=,==,2);eq(==,==,1);
		if(!count)f("base64 '=' sytax error!\n");
		for(int i=0;i<count;i++)putc(u24.arr[i],ofp);
	}
	save();
}
