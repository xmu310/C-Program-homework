#include<stdio.h>
#include<stdint.h>
static double check=0,x,y,dx,dy;
void set_line(double x1,double y1,double x2,double y2){
	if(x1!=x2||y1!=y2)check=1,x=x1,y=y1,dx=x2-x1,dy=y2-y1;
}
int32_t get_mirror(double a,double b,double *c,double *d){
	if(check){
		*c=a-(dy*(a-x)-dx*(b-y))/(dx*dx+dy*dy)*dy*2;
		*d=b+(dy*(a-x)-dx*(b-y))/(dx*dx+dy*dy)*dx*2;
		return 0;
	}else{
		return -1;
	}
}
