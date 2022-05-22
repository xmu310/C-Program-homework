#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#define abbr(x) *(int32_t*)(head+x)
#define WPIX(pos,c,i) op[i][ini+(nt+pos)*3]=op[i][ini+(nt+pos)*3+1]=op[i][ini+(nt+pos)*3+2]=0xFF*c
#define WPIX4(c1,c2,c3,c4,i) do{WPIX(0,c1,i);WPIX(1,c2,i);WPIX(w*2,c3,i);WPIX(w*2+1,c4,i);}while(0)
int main(int argc,char *argv[]){
	FILE *ifp,*ofp;
	int64_t w=0,h=0,nsz,ini=54,x,y,nt,ofd[3],black;
	char head[ini],name[200]={0},*suffix[3]={"layer1","layer2","overlap"},iname[100]={0},*p,*op[3];
	if(argc!=2){printf("invalid syntax!\n");return 0;}
	ifp=fopen(argv[1],"r");
	if(!ifp){printf("fopen failed!\n");return 0;}
	if(getc(ifp)!='B'||getc(ifp)!='M'){printf("Not bmp\n");return 0;}
	rewind(ifp);
	fread(head,1,ini,ifp);
	w=abbr(0x12),h=abbr(0x16),abbr(0x02)=nsz=ini+w*h*12,abbr(0x22)=w*h*12,abbr(0x12)=w*2,abbr(0x16)=h*2;
	strncpy(iname,argv[1],100);
	if(p=strstr(iname,".bmp"))*p=0;
	for(int i=0;i<3;i++){
		snprintf(name,200,"%s_%s.bmp",iname,suffix[i]);
		ofp=fopen(name,"w+");
		truncate(name,nsz);
		fwrite(head,1,ini,ofp);
		fclose(ofp);
		ofd[i]=open(name,O_RDWR);
		op[i]=mmap(0,nsz,PROT_READ|PROT_WRITE,MAP_SHARED,ofd[i],0);
	}
	for(int i=0;i<w*h;i++){
		x=i%w*2,y=i/w*2,nt=y*w*2+x,black=getc(ifp)*0.114+getc(ifp)*0.587+getc(ifp)*0.299<128;
		if(black){WPIX4(1,0,0,1,0);WPIX4(0,1,1,0,1);WPIX4(0,0,0,0,2);}
		if(!black){WPIX4(1,0,0,1,0);WPIX4(1,0,0,1,1);WPIX4(1,0,0,1,2);}
	}
	fclose(ifp);
	for(int i=0;i<3;i++)munmap(op[i],nsz);
	return 0;
}
