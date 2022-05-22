#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<math.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
int32_t fn(FILE *p,long n){int32_t x;fseek(p,n,SEEK_SET);fread(&x,4,1,p);rewind(p);return x;}
int main(){
	char tmp[10000]={0},etmp[10000]={0};
	FILE *p[2];
	int64_t cx,cy,x,y,r,sz,w,h,ini;
	for(int i=0;i<2;i++){
		printf("Please enter the %s image name: ",i?"output":"input");
		memset(tmp,0,sizeof(tmp));
		scanf("%[^\n]",tmp);
		scanf("%*c");
		p[i]=fopen(tmp,i?"w+":"r");
		if(!p[i]){printf("fopen failed!\n");return 0;}
		if(!i&&(getc(p[i])!='B'||getc(p[i])!='M')){printf("Not bmp\n");return 0;}
	}
	printf("Please enter the center: ");
	memset(tmp,0,sizeof(tmp));
	scanf("%[^\n]",tmp);
	if(strpbrk(tmp," ")||sscanf(tmp,"(%ld,%ld%s",&cx,&cy,etmp)!=3||strcmp(etmp,")")){printf("Wrong input!\n");return 0;};
	printf("Please enter the radius: ");
	memset(tmp,0,sizeof(tmp));
	scanf("%*c%[^\n]",tmp);
	if(strpbrk(tmp," ")||sscanf(tmp,"%ld",&r)!=1){printf("Wrong input!\n");return 0;}
	sz=fsize(p[0]),w=fn(p[0],0x12),h=fn(p[0],0x16),cy=h-cy,ini=fn(p[0],0x0A);
	while(ftell(p[0])<ini)putc(getc(p[0]),p[1]);
	for(int i=0;ftell(p[0])<sz;i++){
		x=i%w,y=i/w;
		for(int j=0;j<3;j++)if(hypot(x-cx,y-cy)>r){
			getc(p[0]);
			putc(0xFF,p[1]);
		}else putc(getc(p[0]),p[1]);
	}
	fclose(p[0]);
	fclose(p[1]);
	return 0;
}
