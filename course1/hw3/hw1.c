#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int64_t len(int64_t n){int64_t a=0;while(n!=0)n/=10,a++;return a;}
int main(){
	int64_t w,h,n;
	printf("Please enter the width : ");scanf("%ld",&w);
	if(w<=0){printf("Width should be positive integer!\n");exit(0);}
	printf("Please enter the height: ");scanf("%ld",&h);
	if(h<=0){printf("Height should be positive integer!\n");exit(0);}
	for(int64_t i=0;i<h;i++){
		for(int64_t j=0;j<w;j++){
			int64_t tw=w,th=h,pw=0,ph=-1,d=1,td=1;
			for(int64_t k=1;pw!=j||ph!=i;k++){
				ph+=(d==1?1:(d==3?-1:0)),pw+=(d==2?1:(d==4?-1:0));
				td=(d==1&&ph+1==th?2:(d==2&&pw+1==tw?3:(d==3&&ph+1==h-th?4:(d==4&&pw+1==w-tw+1?1:td))));
				th-=(d==1&&ph+1==th?1:0),tw-=(d==2&&pw+1==tw?1:0),n=k,d=td;
			}
			for(int64_t k=0;k<len(w*h)-len(n);k++)printf(" ");
			printf("%ld ",n);
		}
		printf("\n");
	}
	return 0;
}
