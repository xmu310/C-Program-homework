#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void f(char* s){
	printf("The bidding choice : %s\n",s);
	exit(0);
}
int main(){
	int64_t n[13],h=0,s[4]={0};
	char* str[13]={"1st","2nd","3rd","4th","5th","6th","7th","8th","9th","10 th","11 th","12 th","13 th"};
	for(int i=0;i<13;i++){
		printf("%s card: ",str[i]);
		scanf("%ld",&n[i]);
		if(n[i]<1||n[i]>52){
			printf("Input illegal.(Only allow 1 to 52)\n");
			exit(0);
		}
		for(int j=1;j<=3;j++)if(n[i]%13==10+j)h+=j;
                if(n[i]%13==1)h+=4;
		for(int j=0;j<=3;j++)if((n[i]-1)/13==j)s[j]++;
	}
	printf("---\nHCP: %ld pts\nSuit: %ld-%ld-%ld-%ld\n",h,s[0],s[1],s[2],s[3]);
	if(h>=22)f("2C");
	if(h>=13&&h<=21&&s[0]>=5&&s[0]>=s[1])f("1S");
        if(h>=13&&h<=21&&s[1]>=5)f("1H");
	if(h>=16&&h<=18)f("1NT");
	if(h>=20&&h<=21)f("2NT");
	if(h>=13&&h<=21&&s[2]>=3&&s[2]>=s[3])f("1D");
        if(h>=13&&h<=21&&s[3]>=3)f("1C");
	if(h>=10&&h<=12&&s[0]>=7&&s[0]>=s[1]&&s[0]>=s[2]&&s[0]>=s[3])f("3S");
	if(h>=10&&h<=12&&s[1]>=7&&s[1]>=s[2]&&s[1]>=s[3])f("3H");
        if(h>=10&&h<=12&&s[2]>=7&&s[2]>=s[3])f("3D");
        if(h>=10&&h<=12&&s[3]>=7)f("3C");
        if(h>=10&&h<=12&&s[0]>=6&&s[0]>=s[1]&&s[0]>=s[2])f("2S");
        if(h>=10&&h<=12&&s[1]>=6&&s[1]>=s[2])f("2H");
        if(h>=10&&h<=12&&s[2]>=6)f("2D");
	f("Pass");
	return 0;
}
