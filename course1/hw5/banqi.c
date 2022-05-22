#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
int64_t t,X,Y,now=1,num[16]={1,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7},pcolor[2],show[8][4]={0},color[8][4],type[8][4];
void f(int64_t a[][4],int64_t i,int64_t j,int64_t k,int64_t l){t=a[i][j],a[i][j]=a[k][l],a[k][l]=t;}
void change(int64_t i,int64_t j,int64_t k,int64_t l){f(show,i,j,k,l);f(color,i,j,k,l);f(type,i,j,k,l);}
int d1(int64_t x,int64_t y){return abs(X-x)==1&&Y==y||abs(Y-y)==1&&X==x;}
int test(int64_t x,int64_t y){
        int64_t m=0;
        if(!(x<0||x>7||y<0||y>3)&&show[x][y]==2&&d1(x,y))return 1;
        if(!(x<0||x>7||y<0||y>3)&&show[x][y]==1&&color[x][y]!=pcolor[now]){
                if(type[X][Y]==5&&x==X)for(int64_t i=y+(Y>y?1:-1);(Y-i)*(Y-y)>0;i+=(Y>y?1:-1))if(show[x][i]!=2)m++;
                if(type[X][Y]==5&&y==Y)for(int64_t i=x+(X>x?1:-1);(X-i)*(X-x)>0;i+=(X>x?1:-1))if(show[i][y]!=2)m++;
                if(type[X][Y]!=5&&d1(x,y)&&((type[X][Y]||type[x][y]!=6)&&type[X][Y]<=type[x][y]||type[X][Y]==6&&!type[x][y])||m==1)return 2;
        }
        return 0;
}

