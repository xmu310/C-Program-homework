#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int main(){
	double x[5],y[5],ans=0;
	for(int i=0;i<5;i++){
		printf("Please enter P%d: ",i+1);
		scanf("%lf,%lf",&x[i],&y[i]);
	}
	for(int i=1;i<5;i++){
		for(int j=0;j<i;j++){
			if(x[i]==x[j]&&y[i]==y[j]){
				printf("This is not a pentagon.\n");
				return 0;
			}
		}
	}
	for(int i=0;i<5;i++)ans+=x[i]*y[(i+1)%5]-y[i]*x[(i+1)%5];
	ans=0.5*abs(ans);
	printf("%lf\n",ans);
	return 0;
}
