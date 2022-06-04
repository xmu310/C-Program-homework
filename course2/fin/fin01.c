#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<getopt.h>
int main(int argc,char *argv){
	struct option optl[]={
		{"help",0,&h,1}
		{0,0,0,0}
	};
	char buf[1000]={0},*str[4]={"top left","top right","bottom left","bottom right"},head[54]={0},c,cc;
	int64_t x=0,y=0,tmp[3]={0},w=1024,h=768;
	uint8_t color[5][3];
	head[0x0]='B',head[0x1]='M';
	while((c=getopt_long(argc,argv,"w:h:o:",optl,0))!=-1){
		if(c=='w'){
			if(sscanf(optarg,"%d%c",&w,&cc)!=1||w<0)printf("width should be a positive number\n");
		}else if(c=='h'){
			if(sscanf(optarg,"%d%c",&h,&cc)!=1||h<0)printf("width should be a positive number\n");
		}else if(c=='o'){
			strcpy(buf,optarg);
		}else if(c!=0){
			printf("Syntax error!\n");
			return 0;
		}
	}
	*(uint32_t*)&head[0x2]=w*h*3+54;
	*(uint32_t*)&head[0xA]=54;
	*(uint32_t*)&head[0xE]=40;
	*(uint32_t*)&head[0x12]=w;
	*(uint32_t*)&head[0x16]=h;
	*(uint16_t*)&head[0x1A]=1;
	*(uint16_t*)&head[0x1C]=24;
	*(uint32_t*)&head[0x22]=w*h*3;
	*(uint32_t*)&head[0x26]=9449;
	*(uint32_t*)&head[0x2A]=9449;
	for(int i=0;i<4;i++){
		printf("Please enter (R,G,B) in the %s pixel: ",str[i]);
		if(scanf("%ld,%ld,%ld%c",&tmp[2],&tmp[1],&tmp[0],&c)!=4||c!='\n'){printf("syntax error!\n");return 0;}
		for(int j=0;j<3;j++)if(tmp[j]<0||tmp[j]>255){printf("RGB should be 0-255\n");return 0;}else color[i][j]=tmp[j];
	}
	FILE *fp=fopen(buf,"w+");
	if(!fp){printf("fopen failed!\n");return 0;}
	fwrite(head,1,54,fp);
	for(int i=0;i<w*h;i++){
		x=i%w,y=i/w;
		for(int j=0;j<3;j++)color[4][j]=(double)((w-x)*((h-y)*color[2][j]+y*color[0][j])+x*((h-y)*color[3][j]+y*color[1][j]))/(double)(w*h);
		fwrite(&color[4],1,3,fp);
	}
	printf("Done\n");
	fclose(fp);
	return 0;
}
