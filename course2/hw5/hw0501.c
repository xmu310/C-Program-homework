#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#define f(x) do{printf(x);return 0;}while(0)
#define openchk(x) do{fp=fopen(x,"r");if(!fp){printf("Open "x" failed!\n");return 0;}}while(0)
int main(int argc,char *argv[]){
	FILE *fp;
	int32_t bopt=1,sopt=0,sarg=0,copt=0,carg=1,hopt=0;
	uint64_t total,avail;
	char c,*endp;
	struct option optl[]={
		{"bytes",0,&bopt,0},
		{"kilo",0,&bopt,1},
		{"mega",0,&bopt,2},
		{"seconds",1,0,'s'},
		{"count",1,0,'c'},
		{"help",0,&hopt,1},
		{0,0,0,0}
	};
	while((c=getopt_long(argc,argv,"bs:c:",optl,0))!=-1){
		if(c=='b'){bopt=0;continue;}
		if(c=='s'){sarg=strtol(optarg,&endp,10);if(!*endp&&sarg>0)sopt=1;else f("Error\n");continue;}
		if(c=='c'){carg=strtol(optarg,&endp,10);if(!*endp&&carg>=0)copt=1;else f("Error\n");continue;}
		if(c!=0)f("Syntax error!\n");
	}
	if(optind<argc)f("Syntax error!\n");
	if(hopt){
		openchk("help1.txt");
		while(1){c=getc(fp);if(!feof(fp))putchar(c);else break;}
		fclose(fp);
		return 0;
	}
	for(int i=0;copt?i<carg:(sopt?1:i<1);i++){
		openchk("/proc/meminfo");
		fscanf(fp,"%*[^:]:%lu%*[^:]:%*[^:]:%lu",&total,&avail);
		if(bopt==0)printf("Available: %lu Bytes",avail*1024);
		if(bopt==1)printf("Available: %lu KB",avail);
		if(bopt==2)printf("Available: %lu MB",avail/1024);
		printf(" (%.2lf%%)\n",(double)(avail*100)/(double)total);
		sleep(sarg);
		fclose(fp);
	}
	return 0;
}
