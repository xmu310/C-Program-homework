#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void k(int64_t n){
	for(int64_t i=(n-3)/2;i>=0;i--){
		printf("*");
		for(int64_t j=0;j<i;j++)printf(" ");
		printf("*\n");
	}
	printf("*\n");
	for(int64_t i=0;i<=(n-3)/2;i++){
		printf("*");
		for(int64_t j=0;j<i;j++)printf(" ");
		printf("*\n");
	}
}
