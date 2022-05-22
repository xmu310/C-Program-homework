#include<stdio.h>
#include<stdint.h>
void cal(int64_t arr[3],int64_t q){arr[2]=arr[0]-q*arr[1],arr[0]=arr[1],arr[1]=arr[2];}
int32_t ext_euclidean(uint32_t a,uint32_t b,uint32_t *c){
	if(a<b||a==0||b==0)return -1;
	int64_t q,r[3]={a,b},s[3]={1,0},t[3]={0,1};
	while(r[1]!=0)q=r[0]/r[1],cal(r,q),cal(s,q),cal(t,q);
	if(r[0]==1){
		while(t[0]<0)t[0]+=a;
		while(t[0]>a-1)t[0]-=a;
		*c=t[0];
		return 1;
	}else{
		*c=r[0];
		return 0;
	}
}
