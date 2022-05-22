#include<stdio.h>
#include<errno.h>
#include<string.h>
int main(){
	printf("I wanna open a file which doesn't exist!\n");
	fopen("haha","r");
	printf("\nThe message of perror:\n");
	perror("fopen");
	printf("\nThe message of strerror:\n");
	printf("%s\n",strerror(errno));
}
