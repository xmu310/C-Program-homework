#include<stdio.h>
#include<stdint.h>
#include"hw0404.h"
#define f() do{printf("Illegal input!\n");return 0;}while(0)
#define color(x,y) "\033["xy"m\033[m"
int main(int argc,char *argv[]){
	int64_t fn=0,cho=0,num=0;
	double dnum=0;
	char name[1000]={0},buf[100]={0};
	printf("Please enter which record you wanna cheat (01-10): ");
	if(scanf("%ld",&fn)!=1||fn<1||fn>10)f();
	snprintf(name,1000,"pm2/F1%02ld.GNX",fn);
	FILE *fp=fopen(name,"r+");
	if(!fp){printf("Open record file (%s) failed!\n",name);return 0;}
	printf("-------------------------------\nindex. name (current value)\n-------------------------------\n");
	for(int i=0;1;i+=13){
		fseek(fp,s[i].pos,SEEK_SET);
		num=0;
		fread(&num,1,s[i].byte,fp);
		printf("\033[31m%02d. \033[32m%s \033[m",i,s[i].name);
		if(i>=27&&i<=31){
			snprintf(buf,100,"%ld.%02ld",num/100,num%100);
			printf("\033[33m%7s\033[m ",buf);
		}else printf("\033[33m%7ld\033[m ",num);
		if(i==38)break;
		if(i>=26){printf("\n");i=i-39+1;}
	}
	printf("\n-------------------------------\nPlease enter which thing above you wanna cheat (00-38): ");
	if(scanf("%ld",&cho)!=1||cho<0||cho>38)f();
	fseek(fp,s[cho].pos,SEEK_SET);
	if(cho>=27&&cho<=31){
		printf("Please enter the new value (0-655.35): ");
		if(scanf("%lf",&dnum)!=1||dnum<0||dnum>655.35)f();
		num=dnum*100+0.001;
	}else{
		printf("Please enter the new value (%ld-%ld): ",s[cho].l,s[cho].h);
		if(scanf("%ld",&num)!=1||num<s[cho].l||num>s[cho].h)f();
	}
	fwrite(&num,1,s[cho].byte,fp);
	printf("Success!\n");
	fclose(fp);
	return 0;
}
