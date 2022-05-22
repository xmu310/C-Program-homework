#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int32_t group[19][19]={0};
void f1(int32_t x,int32_t y,int32_t a,int32_t b){
	if(group[a][b]!=0)for(int i=0;i<19;i++)for(int j=0;j<19;j++)if(!(i==a&&j==b)&&group[i][j]==group[a][b])group[i][j]=group[x][y];
	group[a][b]=group[x][y];
}
void find_group(int32_t board[][19],int32_t x,int32_t y){
	if(x+1<19&&board[x+1][y]==1)f1(x,y,x+1,y);
	if(x-1>=0&&board[x-1][y]==1)f1(x,y,x-1,y);
	if(y+1<19&&board[x][y+1]==1)f1(x,y,x,y+1);
	if(y-1>=0&&board[x][y-1]==1)f1(x,y,x,y-1);
}
int32_t max_black_chain(int32_t board[][19]){
	int32_t ans=0,max_group=0,liberty[361]={0},check[361]={0};
	for(int i=0;i<19;i++)for(int j=0;j<19;j++)group[i][j]=0;
	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			if(board[i][j]==1){
				if(group[i][j]==0)max_group+=1,group[i][j]=max_group;
				find_group(board,i,j);
			}
		}
	}
	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			for(int k=0;k<361;k++)check[k]=0;
			if(board[i][j]==0){
				if(i+1<19&&board[i+1][j]==1&&!check[group[i+1][j]])liberty[group[i+1][j]]++,check[group[i+1][j]]++;
				if(i-1>=0&&board[i-1][j]==1&&!check[group[i-1][j]])liberty[group[i-1][j]]++,check[group[i-1][j]]++;
				if(j+1<19&&board[i][j+1]==1&&!check[group[i][j+1]])liberty[group[i][j+1]]++,check[group[i][j+1]]++;
				if(j-1>=0&&board[i][j-1]==1&&!check[group[i][j-1]])liberty[group[i][j-1]]++,check[group[i][j-1]]++;
			}
		}
	}
	for(int i=0;i<361;i++)if(liberty[i]>=ans)ans=liberty[i];
	return ans;
}
