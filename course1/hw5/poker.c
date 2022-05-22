#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int32_t big_two_sort(int8_t cards[]){
	int8_t tmp,a,b;
	for(int8_t i=0;i<13;i++){
		if(cards[i]<1||cards[i]>52)return -1;
		for(int8_t j=i+1;j<13;j++)if(cards[i]==cards[j])return -1;
	}
	for(int8_t i=0;i<13;i++){
		for(int8_t j=i+1;j<13;j++){
			if((cards[i]+10)%13>(cards[j]+10)%13||(cards[i]+10)%13==(cards[j]+10)%13&&cards[i]>cards[j]){
				tmp=cards[i],cards[i]=cards[j],cards[j]=tmp;
			}
		}
	}
	return 0;
}
