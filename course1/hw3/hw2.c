#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	int64_t n[3],d[3][1000]={0},len[3]={0};
	char *s[2]={"first ","second"},*str[3]={"  ","\n+)","\n  "};
	for(int i=0;i<2;i++){
		printf("Please enter the %s number: ",s[i]);
		scanf("%ld",&n[i]);
		if(n[i]<0){printf("Number should be non-negative integer!\n");exit(0);}
		if(n[i]>4294967295){printf("Overflow!\n");exit(0);}
	}
	n[2]=n[0]+n[1];
	if(n[2]>4294967295){printf("Overflow!\n");exit(0);}
	for(int i=0;i<3;i++)for(int j=0;n[i]!=0||n[i]==0&&len[i]==0;j++)d[i][j]=n[i]%10,n[i]/=10,len[i]++;
	for(int i=0;i<3;i++){
		if(i==2){printf("\n--");for(int64_t i=0;i<len[2];i++)printf("--");}
		printf("%s",str[i]);
		for(int64_t j=1;j<=len[2]-len[i];j++)printf("  ");
		for(int64_t j=len[i]-1;j>=0;j--)printf(" %ld",d[i][j]);
	}
	printf("\n");
	return 0;
}
