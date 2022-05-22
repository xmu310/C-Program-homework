#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
int main(){
	FILE *bp=fopen("bible.txt","r");
	FILE *re=fopen("result","w+");
	int64_t bsize=fsize(bp),rsize,cha,ver,num=0;
	char ts[10000]={0},sen[10000]={0},id[10000]={0};
	printf("Please enter the search target: ");
	scanf("%10000[^\n]",ts);
	if(ts[9999]){printf("Found 0 time(s)\n");fclose(bp);fclose(re);system("rm result");return 0;}
	if(!ts[0]){printf("Error\n");fclose(bp);fclose(re);system("rm result");return 0;}
	while(fgetc(bp)=='{'&&ftell(bp)<bsize){
	        fscanf(bp,"%*[^:]:%ld%*[^:]:%ld%*[^:]:\"%[^\"]%*[^:]:%*[^:]:\"%[^\"]%*[^{]",&cha,&ver,sen,id);
		if(strcasestr(sen,ts)){
			num++;
			fprintf(re,"%ld. %s %ld:%ld %s\n",num,id,cha,ver,sen);
		}
	}
	printf("Found %ld time(s)\n",num);
	rsize=fsize(re);
	while(ftell(re)<rsize)printf("%c",getc(re));
	fclose(bp);
	fclose(re);
	system("rm result");
	return 0;
}
