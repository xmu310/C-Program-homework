#include<stdio.h>
#include<setjmp.h>
jmp_buf env;
void f(){
	printf("hi\n");
	longjmp(env,1);
	printf("ha\n");
}
int main(){
	if(setjmp(env)){
		printf("second!\n");
	}else{
		printf("first!\n");
		f();
	}
	return 0;
}
