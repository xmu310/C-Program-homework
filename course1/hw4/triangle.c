#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
static double p1=0,p2=0,p3=0,x1,Y1,x2,y2,x3,y3,a1,a2,a3;
int set_1_point(double x,double y){
	if(p2&&p3&&((y2-y3)*(x-x2)==(x2-x3)*(y-y2))||p2&&x==x2&&y==y2||p3&&x==x3&&y==y3){
		return 0;
	}else{
		p1=1,x1=x,Y1=y;
		return 1;
	}
}
int set_2_point(double x,double y){
	if(p1&&p3&&((y-y3)*(x1-x)==(x-x3)*(Y1-y))||p1&&x==x1&&y==Y1||p3&&x==x3&&y==y3){
		return 0;
	}else{
		p2=1,x2=x,y2=y;
		return 1;
	}
}
int set_3_point(double x,double y){
	if(p1&&p2&&((y2-y)*(x1-x2)==(x2-x)*(Y1-y2))||p1&&x==x1&&y==Y1||p2&&x==x2&&y==y2){
		return 0;
	}else{
		p3=1,x3=x,y3=y;
		return 1;
	}
}
int check(void){
	if(p1&&p2&&p3){
		a1=hypot(x2-x3,y2-y3),a2=hypot(x1-x3,Y1-y3),a3=hypot(x1-x2,Y1-y2);
		return 1;
	}else{
		return 0;
	}
}
double get_perimeter(void){
	if(check()==0)return -1;
	return a1+a2+a3;
}
double get_area(void){
	if(check()==0)return -1;
	return fabs(x1*(y2-y3)+x2*(y3-Y1)+x3*(Y1-y2))/2;
}
double get_1_degree(void){
	if(check()==0)return -1;
	return acos((a2*a2+a3*a3-a1*a1)/2/a2/a3)/acos(-1)*180;
}
double get_2_degree(void){
	if(check()==0)return -1;
	return acos((a1*a1+a3*a3-a2*a2)/2/a1/a3)/acos(-1)*180;
}
double get_3_degree(void){
	if(check()==0)return -1;
	return acos((a1*a1+a2*a2-a3*a3)/2/a1/a2)/acos(-1)*180;
}
double get_inscribed_center_x(void){
	if(check()==0)return 0;
	return (a1*x1+a2*x2+a3*x3)/(a1+a2+a3);
}
double get_inscribed_center_y(void){
	if(check()==0)return 0;
	return (a1*Y1+a2*y2+a3*y3)/(a1+a2+a3);
}
double get_inscribed_center_area(void){
	if(check()==0)return -1;
	return get_area()*2/get_perimeter();
}
double get_circumscribed_center_x(void){
	if(check()==0)return 0;
	return ((x1*x1+Y1*Y1)*(y2-y3)+(x2*x2+y2*y2)*(y3-Y1)+(x3*x3+y3*y3)*(Y1-y2))/2/(x1*(y2-y3)+x2*(y3-Y1)+x3*(Y1-y2));
}
double get_circumscribed_center_y(void){
	if(check()==0)return 0;
	return -((x1*x1+Y1*Y1)*(x2-x3)+(x2*x2+y2*y2)*(x3-x1)+(x3*x3+y3*y3)*(x1-x2))/2/(x1*(y2-y3)+x2*(y3-Y1)+x3*(Y1-y2));
}
double get_circumscribed_center_area(void){
	if(check()==0)return -1;
	return acos(-1)*pow(a1*a2*a3/4/get_area(),2);
}
