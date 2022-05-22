#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
int main(){
	char buf[4][10000]={0},*str[5]={"string","keyword","new word","Original","New"},*now,*post;
	for(int i=0;i<3;i++){
		printf("Please enter the %s:\n",str[i]);
		scanf("%[^\n]",buf[i]);
		scanf("%*c");
	}
	for(int i=0;i<2;i++){
		now=post=(char*)buf[0];
		printf("%s:\n",str[i+3]);
		if(strlen(buf[1])){
			while(post=strcasestr(post,buf[1])){
				while(now!=post)putchar(*now),now++;
				strncpy(buf[3],post,strlen(buf[1]));
				buf[3][strlen(buf[1])]='\0';
				printf("\033[%dm%s\033[m",i+31,buf[i?2:3]);
				now=post+=strlen(buf[1]);
			}
		}
		printf("%s\n",now);
	}
	return 0;
}
