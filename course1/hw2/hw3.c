#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void f(char* s){
        printf("%s\n",s);
        exit(0);
}
int main(){
	int64_t y[2],m[2],d[2],h[2],min[2],m2[2],da[2],re[2]={0},l[12]={31,29,31,30,31,30,31,31,30,31,30,31},wm;
	char* str[2]={"From: ","To: "};
	for(int i=0;i<2;i++){
		printf("%s",str[i]);
		scanf("%ld/%ld/%ld %ld:%ld",&y[i],&m[i],&d[i],&h[i],&min[i]);
		m2[i]=y[i]%4==0&&y[i]%100!=0||y[i]%400==0;
		for(int j=0;j<12;j++)if(m[i]==j+1&&d[i]>l[j]||!m2[i]&&m[i]==2&&d[i]>28)f("Not exist!");
		if(y[i]<1||m[i]<1||m[i]>12||d[i]<1||h[i]<0||h[i]>24||min[i]<0||min[i]>59||h[i]==24&&min[i]!=0)f("Not exist!");
		da[i]=(y[i]-1)*365+(y[i]-1)/4-(y[i]-1)/100+(y[i]-1)/400+d[i]+(m[i]>2&&!m2[i]?0:1);
		for(int j=0;j+1<m[i];j++)da[i]+=l[j];
		for(int j=0;j<=h[i]*60+min[i];j++)if(da[i]%7>1&&(j>540&&j<721||j>810&&j<1111))re[i]++;
	}
	if((da[1]-da[0])*1440+(h[1]-h[0])*60+min[1]-min[0]<0)f("The date of \"To\" earlier than \"From\"!");
        wm=(da[1]-da[0]+1-(da[1]+7)/7+(da[0]+6)/7-(da[1]+6)/7+(da[0]+5)/7)*480-re[0]-(da[1]%7<2?re[1]:480-re[1]);
	printf("Working Hours : %ld hours %ld mins.\n",wm/60,wm%60);
	return 0;
}
