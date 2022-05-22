#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int main(){
	char buf[10000]={0},tc;
	int64_t sz,st,et,cho,rst,ret,tn;
	printf("Please enter the data name: ");
	scanf("%[^\n]",buf);
	scanf("%*c");
	FILE *fp=fopen(buf,"r");
	if(!fp){printf("fopen failed!\n");return 0;}
	printf("Please enter the analysis start time: ");
	memset(buf,0,sizeof(buf));
	scanf("%[^\n]",buf);
	scanf("%*c");
	if(strpbrk(buf," ")||sscanf(buf,"%ld%c",&st,&tc)!=1){printf("invalid input\n");return 0;}
	printf("Please enter the analysis end time: ");
	memset(buf,0,sizeof(buf));
	scanf("%[^\n]",buf);
	scanf("%*c");
	if(strpbrk(buf," ")||sscanf(buf,"%ld%c",&et,&tc)!=1||et<st){printf("invalid input\n");return 0;}
	fseek(fp,0,SEEK_END);
	sz=ftell(fp);
	int64_t m=-4,n=0;
	rewind(fp);
	fscanf(fp,"%*[^\n]\n\n%*[^\n]\n\n");
	while(ftell(fp)<sz){tc=getc(fp);if(n==0&&tc==',')m++;if(tc=='\n')n++;}
	int64_t arr[m][n];
	rewind(fp);
	fscanf(fp,"%*[^\n]\n\n%*[^\n]\n\n");
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(fp,"%*[^0-9]%ld",&arr[j][i]);
	rst=arr[0][0],ret=arr[m-1][0];
	if(st<rst)st=rst;
	if(st>ret)st=-1;
	if(et>ret)et=ret;
	if(et<rst)et=-1;
	while(1){
		printf("--- Menu ---\n");
		printf("1) Which country has the largest population growth?\n");
		printf("2) Which country has the largest population growth rate?\n");
		printf("3) Which country has the smallest population growth, including negative growth?\n");
		printf("4) Which country has the smallest population growth rate, including negative growth?\n");
		printf("5) Which country has the largest population standard deviation?\n");
		printf("6) Which country has the smallest population standard deviation?\n");
		printf("7) Given a country name (case-insensitive), please use linear least squares method to predict the country's population in 2021.\n");
		printf("8) Exit\n");
		printf("Your choice: ");
		memset(buf,0,sizeof(buf));
		scanf("%[^\n]",buf);
		scanf("%*c");
		if(strpbrk(buf," ")||sscanf(buf,"%ld%c",&cho,&tc)!=1||cho<1||cho>8){printf("invalid input\n");return 0;}
		if(cho==8)return 0;
		rewind(fp);
		printf("0\n");
	}
	return 0;
}
