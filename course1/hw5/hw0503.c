#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"polycal.h"
int main(){
	int64_t d[5],p[5][200]={0},max;
	for(int64_t i=0;i<2;i++){
		printf("Please enter p%ld degree: ",i+1);
		scanf("%ld",&d[i]);
		if(d[i]<1||d[i]>100){printf("Degree only allowed 1 to 100!\n");exit(0);}
		printf("Please enter p%ld coefficients: ",i+1);
		for(int64_t j=d[i];j>-1;j--){
			scanf("%ld",&p[i][j]);
			if(j==d[i]&&p[i][j]==0){printf("Error!\n");exit(0);}
		}
	}
	polycal(d,p,max);
	return 0;
}
