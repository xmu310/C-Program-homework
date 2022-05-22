#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	int64_t my,m1,v1,l1,m2,v2,l2,m,r;
	while(1){
		printf("Your movement (3~6): ");
		scanf("%ld",&my);
		if(my>=3&&my<=6)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 1 movement (3~6): ");
		scanf("%ld",&m1);
		if(m1>=3&&m1<=6)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 1 vision (2~10): ");
		scanf("%ld",&v1);
		if(v1>=2&&v1<=10)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 1 location (2~80): ");
		scanf("%ld",&l1);
		if(l1>=2&&l1<=80)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 2 movement (3~6): ");
		scanf("%ld",&m2);
		if(m2>=3&&m2<=6)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 2 vision (2~10): ");
		scanf("%ld",&v2);
		if(v2>=2&&v2<=10)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Enemy 2 location (2~20): ");
		scanf("%ld",&l2);
		if(l2>=2&&l2<=80)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Move: (1) Up (2) Down? ");
		scanf("%ld",&m);
		if(m>=1&&m<=2)break;
		printf("Invalid input!!\n");
	}
	while(1){
		printf("Range (0~3)? ");
		scanf("%ld",&r);
		if(r>=0&&r<=3)break;
		printf("Invalid input!!\n");
	}
	return 0;
}
