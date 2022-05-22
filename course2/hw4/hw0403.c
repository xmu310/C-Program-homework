#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
#define earg(x) (!strcmp(optarg,x))
#define legal(c) (!(c>='0'&&c<='9')&&!(c>='A'&&c<='Z')&&!(c>='a'&&c<='z')&&!(c=='_'))
char text[10000000]={0},kw[500][50]={0};
int main(int argc,char *argv[]){
	FILE *fp;
	struct option os[]={{"linenum",0,0,'n'},{"color",0,0,'c'},{"language",1,0,'l'},{0,0,0,0}};
	int64_t opt_n=0,opt_c=0,opt_l=0,sz,ln=2,mn=0,c1=0,c2=0,cs=0,css=0,slen=0,check=0;
	char c,*lang="C",path[100]="keywords/",*p=text;
	while((c=getopt_long(argc,argv,"ncl:",os,0))!=-1){
		if(c=='n'&&!opt_n){
			opt_n=1;
		}else if(c=='c'&&!opt_c){
			opt_c=1;
		}else if(c=='l'&&!opt_l){
			if(earg("C")||earg("C++")||earg("JAVA")||earg("JS")||earg("Rust")){
				opt_l=1,lang=optarg;
			}else{
				printf("This language is not supported!\n");
				return 0;
			}
		}else{
			printf("Syntax error!\n");
			return 0;
		}
	}
	if(optind!=argc-1){
		printf("Syntax error!\n");
		return 0;
	}else if(!(fp=fopen(argv[optind],"r"))){
		printf("Open failed!\n");
		return 0;
	}
	fseek(fp,0,SEEK_END);
	sz=ftell(fp);
	if(opt_n){
		rewind(fp);
		snprintf(text,100,"001. ");
		for(int i=0;i<sz-1;i++)if((text[strlen(text)]=getc(fp))=='\n'){snprintf(text+strlen(text),100,"%03ld. ",ln);ln++;}
	}else{
		rewind(fp);
		for(int i=0;i<sz-1;i++)text[strlen(text)]=getc(fp);
	}
	fclose(fp);
	if(!opt_c){printf("%s\n",text);return 0;}
	fp=fopen(strncat(path,lang,100),"r");
	if(!fp){printf("%s is not exits!\n",path);return 0;}
	while(fscanf(fp,"%[^\n]\n",kw[mn])==1)mn++;
	while(*p){
		if(c1){
			slen=0;
			while(*(p-(slen+1))=='\\')slen++;
			if(slen%2==0&&*p=='\'')c1=0;
			printf("%c",*p);
			p++;
			continue;
		}else if(c2){
			slen=0;
			while(*(p-(slen+1))=='\\')slen++;
			if(slen%2==0&&*p=='\"')c2=0;
			printf("%c",*p);
			p++;
			continue;
		}else if(cs){
			if(*p=='\n')cs=0;
			printf("%c",*p);
			p++;
			continue;
		}else if(css){
			if(*p=='*'&&*(p+1)=='/'){
				css=0;
				printf("*/");
				p+=2;
			}else{
				printf("%c",*p);
				p++;
			}
			continue;
		}
		if(!c1&&*p=='\'')c1=1;
		if(!c2&&*p=='\"')c2=1;
		if(!cs&&*p=='/'&&*(p+1)=='/')cs=1;
		if(!css&&*p=='/'&&*(p+1)=='*')css=1;
		check=0;
		for(int i=0;i<mn;i++){
			if(!strncmp(p,kw[i],strlen(kw[i]))&&legal(*(p-1))&&legal(*(p+strlen(kw[i])))){
				printf("\033[31m%s\033[m",kw[i]);
				p+=strlen(kw[i]);
				c1=c2=cs=css=0;
				check=1;
				break;
			}
		}
		if(!check){printf("%c",*p);p++;}
	}
	printf("\n");
	return 0;
}
