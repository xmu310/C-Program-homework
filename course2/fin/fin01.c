#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
int main(int argc,char *argv[]){
	int64_t x=0,y=0,tmp[3]={0},w=1024,h=768;
	int help=0;
	struct option optl[]={
		{"help",0,&help,1},
		{0,0,0,0}
	};
	char buf[1000]="output.bmp",*str[4]={"top left","top right","bottom left","bottom right"},head[54]={0},c,cc;
	uint8_t color[5][3];
	while((c=getopt_long(argc,argv,"w:h:o:",optl,0))!=-1){
		if(c=='w'){
			if(sscanf(optarg,"%ld%c",&w,&cc)!=1||w<0||w>2000){printf("width should be 0-2000\n");return 0;}
		}else if(c=='h'){
			if(sscanf(optarg,"%ld%c",&h,&cc)!=1||h<0||h>2000){printf("width should be 0-2000\n");return 0;}
		}else if(c=='o'){
			strcpy(buf,optarg);
		}else if(c!=0){
			printf("Syntax error!\n");
			return 0;
		}
	}
	if(argc-optind!=0){printf("Syntax error!\n");return 0;}
	if(help){
		printf("Usage:\n");
		printf("  ./fin01 [options]\n");
		printf("    -w: the width of the output figure. (Default: 1024)\n");
		printf("    -h: the height of the output figure. (Default: 768)\n");
		printf("    -o: the output file name. (Default: output.bmp)\n");
		printf("    --help: this message\n");
		return 0;
	}
	head[0x0]='B',head[0x1]='M';
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
