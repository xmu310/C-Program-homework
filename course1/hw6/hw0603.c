#include<stdio.h>
#include<stdint.h>
int main(){
	int64_t n,d_i,d;
	int8_t *d_ptr;
	printf("Please input an integer: ");
	scanf("%ld",&n);
	d_ptr=(int8_t*)&n;
	while(1){
		printf("The integer: %ld\n",n);
		for(int64_t i=0;i<8;i++)printf("(%ld) 0x%02hhX ",i+1,*(d_ptr+7-i));
		printf("\nPlease enter the position (1-8, 0: End): ");
		scanf("%ld",&d_i);
		while(d_i<0||d_i>8){
			printf("Error!\nPlease enter the position (1-8, 0: End): ");
			scanf("%ld",&d_i);
		}
		if(d_i==0)return 0;
		printf("Please enter the new value (0-255): ");
		scanf("%ld",&d);
		while(d<0||d>255){
			printf("Error!\nPlease enter the new value (0-255): ");
			scanf("%ld",&d);
		}
		*(d_ptr+8-d_i)=d;
		printf("---\n");
	}
}
