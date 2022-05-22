#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
int32_t fn(FILE *p,long n){int32_t x;fseek(p,n,SEEK_SET);fread(&x,4,1,p);rewind(p);return x;}
void f(){printf("The text format is invalid!\n");exit(0);}
int main(){
	int64_t ini,x,y,sz,w,h,m,n,step,cm,cn,dm,dn,blkcm,blkcn;
	char tmp[10000],head[0x36]={0},name[100],tmpc;
	FILE *fp[2];
	for(int i=0;i<2;i++){
		printf("Please enter the %s: ",i?"puzzle":"image");
		memset(tmp,0,sizeof(tmp));
		scanf("%[^\n]",tmp);
		scanf("%*c");
		fp[i]=fopen(tmp,"r");
		if(!fp[i]||!i&&(getc(fp[i])!='B'||getc(fp[i])!='M')){printf("fopen failed\n");return 0;};
	}
	sz=fsize(fp[0]),w=fn(fp[0],0x12),h=fn(fp[0],0x16),ini=fn(fp[0],0x0A);
	fread(head,0x36,1,fp[0]);
	if(fscanf(fp[1],"%ld %ld\n%ld",&m,&n,&step)!=3||m<=0||m>w||n<=0||n>h||step<=0)f();
	int64_t blk[m][n],pn[m][n],blkw=(w-(m+1)*3)/m,blkh=(h-(n+1)*3)/n,pblk[m][n];
	for(int i=0;i<m;i++)for(int j=0;j<n;j++)pblk[i][j]=j*m+i;
	for(int i=0;i<step;i++){
		int64_t dif=0,difn[2][2]={0},difmn[2][2];
		for(int j=0;j<n;j++)for(int k=0;k<m;k++)if(fscanf(fp[1],"%ld",&blk[k][j])==1)blk[k][j]--;else f();
		if(!i){
			for(int j=0;j<m;j++)for(int k=0;k<n;k++)if(blk[j][k]!=pblk[j][k])if(blk[j][k]==-1&&!dif)dif++;else f();
			if(dif!=1)f();
		}
		if(i){
			for(int j=0;j<m;j++)for(int k=0;k<n;k++)if(blk[j][k]!=pblk[j][k])
				if(dif<2){
					difn[dif][0]=blk[j][k],difn[dif][1]=pblk[j][k];
					difmn[dif][0]=j,difmn[dif][1]=k;
					dif++;
				}else f();
			if(dif!=2||difn[0][0]!=difn[1][1]||difn[0][1]!=difn[1][0])f();
			if(!(difmn[0][0]==difmn[1][0]&&abs(difmn[0][1]-difmn[1][1])==1||difmn[0][1]==difmn[1][1]&&abs(difmn[0][0]-difmn[1][0])==1))f();
		}
		for(int i=0;i<m;i++)for(int j=0;j<n;j++)pblk[i][j]=blk[i][j];
	}
	if(fscanf(fp[1]," %c",&tmpc)==1)f();
	rewind(fp[1]);
	fscanf(fp[1],"%ld %ld\n%ld",&m,&n,&step);
	for(int i=0;i<step;i++){
		for(int j=0;j<n;j++)for(int k=0;k<m;k++)fscanf(fp[1],"%ld",&blk[k][j]),blk[k][j]--;
		memset(pn,0,sizeof(pn));
		memset(name,0,sizeof(name));
		snprintf(name,100,"%d.bmp",i);
		FILE *re=fopen(name,"w");
		fwrite(head,0x36,1,re);
		for(int j=0;j<w*h;j++){
			x=j%w,y=h-1-j/w;
			cm=x/(blkw+3),cn=y/(blkh+3);
			dm=x%(blkw+3),dn=y%(blkh+3);
			if(cm>=m||cn>=n||dm<3||dn<3){
				for(int k=0;k<3;k++)putc(0,re);
			}else if(blk[cm][cn]==-1){
				for(int k=0;k<3;k++)putc(0xFF,re);
			}else{
				blkcm=blk[cm][cn]%m,blkcn=blk[cm][cn]/m;
				x=3+(blkw+3)*blkcm+pn[cm][cn]%blkw,y=3+(blkh+3)*blkcn+(blkh-pn[cm][cn]/blkw);
				fseek(fp[0],ini+((h-y)*w+x)*3,SEEK_SET);
				for(int k=0;k<3;k++)putc(getc(fp[0]),re);
				pn[cm][cn]++;
			}
		}
		fclose(re);
	}
	fclose(fp[0]);
	fclose(fp[1]);
	return 0;
}
