#include<stdio.h>
int main(){
	int re_p,re_s,x=10,y=10,z=10;
	re_p=printf("Haha!\n");
	printf("The printf(\"Haha!\\n\")'s return value is %d.\n\n",re_p);
	printf("The old (x,y,z)=(%d,%d,%d)\n",x,y,z);
	printf("Please enter new (x,y,z):");
	re_s=scanf("(%d,%d,%d)",&x,&y,&z);
	printf("The scanf((%%d,%%d,%%d),&x,&y,&z)'s return value is %d.\n",re_s);
	printf("The new (x,y,z)=(%d,%d,%d)\n",x,y,z);
}
