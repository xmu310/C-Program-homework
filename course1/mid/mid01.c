#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int64_t a,b,c=0,n0=0,n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0;
void nright(int64_t n){
	if(n<0){printf("error!\n");exit(0);}
	if(n==0){n0++;return;}
	while(n!=0){
		if(n%10<n/10%10){printf("error!\n");exit(0);}
		if(n%10==9)n9++;
		if(n%10==8)n8++;
		if(n%10==7)n7++;
		if(n%10==6)n6++;
		if(n%10==5)n5++;
		if(n%10==4)n4++;
		if(n%10==3)n3++;
		if(n%10==2)n2++;
		if(n%10==1)n1++;
		n/=10;
	}
}
int main(){
	printf("Please enter the 1st integer: ");
	scanf("%ld",&a);
	nright(a);
        printf("Please enter the 2nd integer: ");
	scanf("%ld",&b);
	nright(b);
	for(int i=1;i<=n9;i++){
		c=c*10+9;
	}
	for(int i=1;i<=n8;i++){
                c=c*10+8;
        }
	for(int i=1;i<=n7;i++){
                c=c*10+7;
        }
	for(int i=1;i<=n6;i++){
                c=c*10+6;
        }
	for(int i=1;i<=n5;i++){
                c=c*10+5;
        }
	for(int i=1;i<=n4;i++){
                c=c*10+4;
        }
	for(int i=1;i<=n3;i++){
                c=c*10+3;
        }
	for(int i=1;i<=n2;i++){
                c=c*10+2;
        }
	for(int i=1;i<=n1;i++){
                c=c*10+1;
        }
	for(int i=1;i<=n0;i++){
                c=c*10+0;
        }
	printf("%02ld\n",c);
	return 0;
}
