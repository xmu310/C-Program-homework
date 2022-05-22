#include<stdio.h>
#include<stdint.h>
int main(){
	int64_t n,s=0,x=0;
	printf("Start\n");
	while(s!=7){
		printf("Please enter an integer: ");scanf("%ld",&n);
		if(s==0){
			if(n==10||n==35)s=1;
			if(n==11)s=3;
			if(n==20||n==78)s=5;
		}else if(s==1){
			if(n==19)s=2;
			if(n==12||n==36)s=6;
		}else if(s==2){
			if(n==99)s=7,x=1;
			if(n==43)x=1;
			if(x==0)s=0;
		}else if(s==3){
			s=4;
		}else if(s==4){
			s=6;
		}else if(s==5){
			if(n==1)s=4,x=1;
			if(n==2)s=6,x=1;
			if(x==0)s=0;
		}else if(s==6){
			if(n==108)s=7,x=1;
			if(x==0)s=5;
		}
		if(s==0)printf("Start\n");
		if(s>=1&&s<=6)printf("S%ld\n",s);
		x=0;
	}
	printf("Final\n");
	return 0;
}
