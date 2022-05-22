#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void polycal(int64_t d[5],int64_t p[5][200],int64_t max){
        char *s[5]={"p1","p2","p1 + p2","p1 - p2","p1 * p2"};	
	d[2]=d[3]=max=(d[0]>d[1]?d[0]:d[1]),d[4]=d[0]+d[1];
        for(int64_t i=max;i>0&&p[0][i]+p[1][i]==0;i--)d[2]--;
        for(int64_t i=max;i>0&&p[0][i]-p[1][i]==0;i--)d[3]--;
        for(int64_t i=max;i>-1;i--)p[2][i]=p[0][i]+p[1][i],p[3][i]=p[0][i]-p[1][i];
        for(int64_t i=d[4];i>-1;i--)for(int64_t j=0;j<d[0]+1&&i-j>-1;j++)p[4][i]+=p[0][j]*p[1][i-j];
        for(int64_t i=0;i<5;i++){
                printf("%s: ",s[i]);
                for(int64_t j=d[i];j>-1;j--){
                        if(j==d[i]&&p[i][j]<0)printf("-");
                        if(j!=d[i]&&p[i][j]!=0)printf(p[i][j]>0?" + ":" - ");
                        if(j>1&&p[i][j]!=0&&p[i][j]!=1&&p[i][j]!=-1)printf("%ldx^%ld",p[i][j]>0?p[i][j]:-p[i][j],j);
                        if(j>1&&(p[i][j]==1||p[i][j]==-1))printf("x^%ld",j);
                        if(j==1&&p[i][j]!=0&&p[i][j]!=1&&p[i][j]!=-1)printf("%ldx",p[i][j]>0?p[i][j]:-p[i][j]);
                        if(j==1&&(p[i][j]==1||p[i][j]==-1))printf("x");
                        if(j==0&&p[i][j]!=0)printf("%ld",p[i][j]>0?p[i][j]:-p[i][j]);
                }
                if(d[i]==0&&p[i][0]==0)printf("0");
                printf("\n");
        }
}
