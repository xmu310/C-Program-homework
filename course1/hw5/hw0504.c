#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include"banqi.h"
int main(){
	int64_t x2,y2,init=1,step=0,testall,check1,check2,turn,alive[2]={16,16};
	for(int64_t i=0;i<4;i++)for(int64_t j=0;j<8;j++)color[j][i]=(i*8+j)/16,type[j][i]=num[(i*8+j)%16]-1;
	srand(time(0));
	for(int64_t i=0;i<1000;i++)change(rand()%8,rand()%4,rand()%8,rand()%4);
	while(step!=50&&alive[0]&&alive[1]){
		testall=check1=check2=turn=0,now=(now+1)%2;
		for(int64_t i=0;i<4;i++){
			i?0:printf("  1 2 3 4 5 6 7 8\n +---------------+\n"),printf("%ld|",i+1);
			for(int j=0;j<8;j++)show[j][i]!=1?printf(show[j][i]?" |":"*|"):printf("%c|",(color[j][i]?'A':'1')+(char)type[j][i]);
			printf(i!=3?"\n |---------------|\n":"\n +---------------+\n");
		}
		for(int64_t i=0;!check1;i++){
			i?printf("Illegal input!\n"):0,printf("Player %ld (x,y): ",now+1);
			scanf("%ld,%ld",&X,&Y);
			X--,Y--,check1=!(X<0||X>7||Y<0||Y>3)&&show[X][Y]!=2&&!(show[X][Y]==1&&color[X][Y]!=pcolor[now]);
		}
		if(init)init=0,pcolor[0]=color[X][Y],pcolor[1]=(pcolor[0]+1)%2;
		if(!show[X][Y])show[X][Y]=1,turn=1;
		if(!turn)for(int64_t i=0;i<8;i++)for(int64_t j=0;j<4;j++)if(test(i,j))testall=1;
		if(!turn&&!testall)printf("Pass!\n");
		for(int64_t i=0;!turn&&testall&&!check2;i++){
			i?printf("Illegal input!\n"):0,printf("To (x,y): ");
			scanf("%ld,%ld",&x2,&y2);
			x2--,y2--,check2=test(x2,y2);
		}
		!turn&&testall?(show[x2][y2]=2,change(X,Y,x2,y2),check2==2?alive[(now+1)%2]--:0):0,step=turn||check2==2?0:step+1;
	}
	alive[0]&&alive[1]?printf("Tie!\n"):printf("The winner is player %ld!\n",now+1);
	return 0;
}
