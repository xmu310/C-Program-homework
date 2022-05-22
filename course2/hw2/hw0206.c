#include<stdio.h>
#include<stdint.h>
int main(){
	int32_t number=0;
	scanf("%d",&number);
	int32_t bit=1;
	bit=bit<<31;
	printf("if signed:\n");
	for(int i=0;i<32;i++){
		if(bit&number)printf("1");else printf("0");
		bit=bit>>1;
	}
	printf("\n");
	uint32_t new_bit=1;
	new_bit=new_bit<<31;
	printf("if unsigned:\n");
	for(int i=0;i<32;i++){
		if(new_bit&number)printf("1");else printf("0");
		new_bit=new_bit>>1;
	}
	printf("\n(This is correct!)\n");
}
