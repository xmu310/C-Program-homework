#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	int64_t x1,y1,x2,y2,l,w;
	printf("First point (x,y): ");
	scanf("%ld,%ld",&x1,&y1);
	printf("Second point (x,y): ");
	scanf("%ld,%ld",&x2,&y2);
	l=abs(x1-x2),w=abs(y1-y2);
	if(l==0||w==0){
		printf("This is not a rectangle!\n");
		exit(0);
	}
	printf("Perimeter --> %ld\n",(l+w)*2);
	printf("Area --> %ld\n",l*w);
	return 0;
}
