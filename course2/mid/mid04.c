#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<math.h>
int64_t fsize(FILE *p){fseek(p,0,SEEK_END);int64_t re=ftell(p);rewind(p);return re;}
int32_t fn(FILE *p,long n){int32_t x;fseek(p,n,SEEK_SET);fread(&x,4,1,p);rewind(p);return x;}
int main(){
        char tmp[10000]={0},ec=0,color[3];
        FILE *p[2];
        double ca,sa,angle,ratio,dx,dy;
	int64_t anglei,x,y,ox,oy,oi,sz,w,h,ini,ddx,ddy;
        printf("Please enter the output image name: ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        printf("Please enter the size (x,y): ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        printf("Please enter the line width (1,2,3): ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        printf("Please enter the equation file name: ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        printf("Please enter the x boundary (unit:pi): ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        return 0;
}
