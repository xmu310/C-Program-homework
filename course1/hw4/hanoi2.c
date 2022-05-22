#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void hanoi2(int64_t n){
	int64_t max=(1<<n-1)-1,a[20]={1},b[20]={2},c[20]={3},x=0;
	for(int64_t i=0;i<=max;i++){
		for(int64_t j=x+1;j<n;j++){
			if((i&1<<n-1-j)==0){
				a[j]=a[j-1],b[j]=c[j-1],c[j]=b[j-1];
			}else{
				a[j]=c[j-1],b[j]=b[j-1],c[j]=a[j-1];
			}
		}
        	printf("move disk 1 to rod %ld\n",b[n-1]);
		if(i==max)break;
		for(int64_t j=0;j<n;j++)if((i&1<<n-1-j)!=(i+1&1<<n-1-j)){x=j-1;break;}
        	printf("move disk %ld to rod %ld\n",n-x,b[x]);
	}
}
