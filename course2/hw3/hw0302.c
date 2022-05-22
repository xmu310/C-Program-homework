#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<stdlib.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
int main(){
	FILE *p;
	char buf[10000],gar[10000],*endp;
	int64_t ps,h[3]={0},m[3]={0},s[3]={0},ms[3]={0},t;
	double speed;
	printf("Open a srt file: ");
	scanf("%[^\n]",buf);
	p=fopen(buf,"r");
	if(!p){printf("Open failed!\n");return 0;}
	ps=fsize(p);
	printf("Speed (0.5-2): ");
	scanf("%*c%[^\n]",buf);
	speed=strtod(buf,&endp);
	if(*endp||speed<0.5||speed>2){printf("error!\n");return 0;}
	while(fscanf(p,"%[^\n]",gar)&&ftell(p)<ps){
		fscanf(p,"\n%ld:%ld:%ld,%ld --> %ld:%ld:%ld,%ld\n%[^\n]\n\n",&h[1],&m[1],&s[1],&ms[1],&h[2],&m[2],&s[2],&ms[2],buf);
		system("clear");
		t=(((h[1]-h[0])*60+(m[1]-m[0]))*60+s[1]-s[0])*1000+ms[1]-ms[0];
		usleep(t*1000/speed);
		printf("%s\n",buf);
		fflush(stdout);
		t=(((h[2]-h[1])*60+(m[2]-m[1]))*60+s[2]-s[1])*1000+ms[2]-ms[1];
		usleep(t*1000/speed);
		h[0]=h[2],m[0]=m[2],s[0]=s[2],ms[0]=ms[2];
	}
	fclose(p);
	return 0;
}
