#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
int main(){
	double t1,t2,n1=1,n2,s1,s2,h,shift=0;
	int64_t n;
	printf("Incidence angle: ");
	scanf("%lf",&t1);
	if(t1<0||t1>=90){printf("only allow 0<=angle<90\n");exit(0);}
	t1=t1*acos(-1)/180;
	s1=sin(t1);
	printf("How many layers: ");
	scanf("%ld",&n);
	if(n<1){printf("error\n");exit(0);}
	for(int64_t i=1;i<=n;i++){
		printf("Layer %ld's refractive index: ",i);
		scanf("%lf",&n2);
		if(n2<1){printf("refractive index can't less than 1!\n");exit(0);}
		printf("Layer %ld's height: ",i);
		scanf("%lf",&h);
		if(h<=0){printf("height should be positive!\n");exit(0);}
		s2=n1*s1/n2;
		t2=asin(s2);
		shift+=h*tan(t2);
		s1=s2,t1=t2,n1=n2;
	}
	printf("The shift: %lf\n",shift);
	return 0;
}
