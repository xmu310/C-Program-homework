#include<stdio.h>
#include<stdint.h>
#include<math.h>
double get_mean(const int32_t input[],size_t size){
	double sum=0;
	for(size_t i=0;i<size;i++)sum+=input[i];
	return (double)sum/(double)size;
}
double get_median(const int32_t input[],size_t size){
	double median;
	int32_t tmp[size],t;
	for(size_t i=0;i<size;i++)tmp[i]=input[i];
	for(size_t i=0;i<size;i++)for(size_t j=i+1;j<size;j++)if(tmp[i]>tmp[j])t=tmp[i],tmp[i]=tmp[j],tmp[j]=t;
	if(size%2==1)return (double)tmp[(size-1)/2];
	if(size%2==0)return (double)(tmp[size/2]+tmp[size/2-1])/(double)2;
}
int32_t get_mode(const int32_t input[],size_t size){
	int32_t mode,m[size],n[size],check=0;
	size_t num=0;
	for(size_t i=0;i<size;i++)m[i]=n[i]=0;
	for(size_t i=0;i<size;i++){
		check=0;
		for(size_t j=0;j<num;j++)if(input[i]==m[j])check=1,n[j]++;
		if(check==0)m[num]=input[i],n[num]++,num++;
	}
	mode=m[0];
	for(size_t i=0;i<num-1;i++)if(n[i]<n[i+1]||n[i]==n[i+1]&&m[i]<m[i+1])mode=m[i+1];
	return mode;
}
double get_stddev(const int32_t input[],size_t size){
	int32_t sum=0,sqsum=0;
	for(size_t i=0;i<size;i++)sum+=input[i],sqsum+=input[i]*input[i];
	return sqrt((double)sqsum/(double)size-((double)sum/(double)size)*((double)sum/(double)size));
}
