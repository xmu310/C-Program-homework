#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
char re[10000001]={0};
void f(){printf("error\n");exit(0);}
int main(){
	int32_t check=1,start,final=0,che0=0,index=0;
	char n,tmp[3]={0};
	printf("Please enter the hex string: ");
	while((n=getchar())!='\n'){
		if(!(n>='0'&&n<='9'||n>='a'&&n<='f'||n>='A'&&n<='F'))f();
		check=!check,tmp[check]=n;
		if(check){
			start=(int32_t)strtol(tmp,NULL,16);
			for(int i=0;i<8;i++)final=final*2+start%2,start/=2;
			if(final==0){che0=1;break;}
			if(final>=0x20&&final<=0x7E)re[index]=final,index++,final=0;else f();
		}
	}
	if(!check||!che0)f();
	printf("%s\n",re);
	return 0;
}
