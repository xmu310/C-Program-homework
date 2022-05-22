#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<math.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
void fch(FILE *fp,int64_t pn,int64_t data,int64_t n){fseek(fp,pn,SEEK_SET);fwrite(&data,1,n,fp);}
int32_t fn(FILE *p,long n){int32_t x;fseek(p,n,SEEK_SET);fread(&x,4,1,p);rewind(p);return x;}
int main(){
	char tmp[10000];
	FILE *p[2];
	int64_t sz,h=14,h1=40,h2=12,ini;
	struct{char :3;char b:5;char :2;char g:6;char :3;char r:5;}__attribute__((packed))s24;
	struct{char b:5;char g:6;char r:5;}__attribute__((packed))s16;
	for(int i=0;i<2;i++){
		printf("Please enter the %s image name: ",i?"output":"input");
		memset(tmp,0,sizeof(tmp));
		scanf("%[^\n]",tmp);
		scanf("%*c");
		p[i]=fopen(tmp,i?"w+":"r");
		if(!p[i]){printf("error!\n");return 0;}
		if(!i&&(getc(p[i])!='B'||getc(p[i])!='M')){printf("Not bmp!\n");return 0;}
	}
	sz=fsize(p[0]),ini=fn(p[0],0x0A);
	while(ftell(p[0])<h+h1)putc(getc(p[0]),p[1]);
	int64_t rawnsz=(sz-h-h1)/3*2,nsz=h+h1+h2+rawnsz;
	int64_t bi[][2]={{0x02,rawnsz},{0x0A,h+h1+h2},{0x0E,h1+h2},{0x1C,16},{0x1E,3},{0x22,nsz},{0x36,0xF800},{0x3A,0x07E0},{0x3E,0x001F}};
	for(int i=0;i<sizeof(bi)/sizeof(int64_t [2]);i++)fch(p[1],bi[i][0],bi[i][1],bi[i][0]!=0x1C?4:2);
	fseek(p[0],ini,SEEK_SET);
	while(ftell(p[0])<sz){
		fread(&s24,3,1,p[0]);
		s16.b=s24.b,s16.g=s24.g,s16.r=s24.r;
		fwrite(&s16,2,1,p[1]);
	}
	printf("Done!\n");
	fclose(p[0]);
	fclose(p[1]);
	return 0;
}
