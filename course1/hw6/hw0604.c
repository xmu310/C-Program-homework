#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void Start(int64_t *tn,int64_t *ts){
	printf("Start\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=!(*tn-10)+!(*tn-35)+!(*tn-11)*3+!(*tn-20)*5+!(*tn-78)*5;
}
void S1(int64_t *tn,int64_t *ts){
	printf("S1\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=!(*tn-19)*2+!(*tn-12)*6+!(*tn-36)*6,*ts+=!*ts;
}
void S2(int64_t *tn,int64_t *ts){
	printf("S2\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=!(*tn-43)*2+!(*tn-99)*7;
}
void S3(int64_t *tn,int64_t *ts){
	printf("S3\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=4;
}
void S4(int64_t *tn,int64_t *ts){
	printf("S4\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=6;
}
void S5(int64_t *tn,int64_t *ts){
	printf("S5\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=!(*tn-1)*4+!(*tn-2)*6;
}
void S6(int64_t *tn,int64_t *ts){
	printf("S6\nPlease enter an integer: ");scanf("%ld",tn);
	*ts=!(*tn-108)*7,*ts+=!*ts*5;
}
void Final(int64_t *tn,int64_t *ts){
	printf("Final\n");
	exit(0);
}
int main(){
	int64_t n=0,s=0;
	void (*state[8])(int64_t*,int64_t*)={Start,S1,S2,S3,S4,S5,S6,Final};
	while(1){state[s](&n,&s);}
	return 0;
}
