#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#define fch1(x,y) do{if(*c=='0'+x){*c='0'+y;return;}}while(0)
#define fch2(x,y) do{if(*c=='0'+x&&strspn(c-1,"ptk")){*c='0'+y;return;}}while(0)
#define fch3(x,y) do{if(*c=='0'+x&&*(c-1)=='h'){*(c-1)='0'+y,*c=0;return;}}while(0)
void fch(char *s){
	char *c=s+strlen(s)-1;
	fch1(1,7);fch1(2,1);fch1(3,2);fch1(5,7);fch1(7,3);fch2(4,8);fch3(4,2);fch2(8,4);fch3(8,3);
}
int main(){
	char text[1000],tmp[1000],*p,sp[100][1000]={0},c,cmd[10000]={0};
	int64_t count=0,N=0;
	FILE *ifp,*ofp;
	struct{char p1[4];uint32_t N36;char p2[32];uint32_t N;}s;
	printf("input: ");
	scanf("%[^\n]",text);
	strcpy(tmp,text);
	for(int i=0;1;i++){
		p=strtok(i?NULL:tmp," -.");
		count++;
		strcpy(sp[i],p?p:text);
		if(!p)break;
	}
	for(int i=0;i<count;i++){
		if(i<count-2)fch(sp[i]);
		if(i<count-1)strcat(sp[i],".");
	}
	printf("output: ");
	for(int i=0;i<count;i++){
		printf("%s ",sp[i]);
		if(i==count-1)for(p=sp[i];*p;p++)if(*p==' ')*p=='+';
		strcpy(tmp,"bangtsam?taibun=");
		strcat(tmp,sp[i]);
		strcpy(sp[i],tmp);
	}
	printf("\n");
	fflush(stdout);
	for(int i=0;i<count;i++){
		snprintf(cmd,10000,"rm -f '%s'",sp[i]);
		system(cmd);
		snprintf(cmd,10000,"wget -nv 'https://hapsing.ithuan.tw/%s'",sp[i]);
		system(cmd);
	}
	ofp=fopen("out.wav","w+");
	if(!ofp){printf("out.wav open failed!\n");return 0;}
	for(int i=0;i<count;i++){
		ifp=fopen(sp[i],"r");
		if(!ifp){printf("%s open failed!\n",sp[i]);return 0;}
		fread(&s,1,44,ifp);
		N+=s.N;
		if(!i)fwrite(&s,1,44,ofp);
		while(1){c=getc(ifp);if(feof(ifp))break;putc(c,ofp);}
		fclose(ifp);
		snprintf(cmd,10000,"rm -f '%s'",sp[i]);
		system(cmd);
	}
	s.N=N,s.N36=s.N+36;
	rewind(ofp);
	fwrite(&s,1,44,ofp);
	printf("out.wav has been generated\n");
	fclose(ofp);
	return 0;
}
