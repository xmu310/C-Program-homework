#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
double er(int64_t r,int64_t n){
	double ans=2*r;
	for(int64_t i=0;i<n-1;i++)ans=ans*(double)r/(ans+(double)r)+(double)r;
	return ans;
}
