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
        printf("Please enter the file name: ");
        scanf("%[^\n]",tmp);
        scanf("%*c");
        p[0]=fopen(tmp,"r");
                if(!p[0]){printf("fopen failed!\n");return 0;}
                if(getc(p[0])!='B'||getc(p[0])!='M'){printf("Not bmp\n");return 0;}
        printf("Rotation angle (int, 0-360): ");
        memset(tmp,0,sizeof(tmp));
        scanf("%[^\n]",tmp);
        if(strpbrk(tmp," ")||sscanf(tmp,"%ld%c",&anglei,&ec)!=1||anglei<0||anglei>360){printf("Wrong input!\n");return 0;}
        sz=fsize(p[0]),w=fn(p[0],0x12),h=fn(p[0],0x16),ini=fn(p[0],0x0A);
	angle=(double)anglei*acos(-1)/180,ca=cos(angle),sa=sin(angle),dx=ca*w-sa*h,dy=sa*w+ca*h,ratio=dx>=w?(double)w/dx:(double)h/dy;
	ddx=w/2-(ca*(w/2)-sa*(h/2))*ratio,ddy=h/2-(sa*(w/2)+ca*(h/2))*ratio;
	p[1]=fopen("output.bmp","w+");
        while(ftell(p[0])<ini)putc(getc(p[0]),p[1]);
        while(ftell(p[1])<sz)putc(0xffffff,p[1]);
	for(int i=0;ftell(p[0])<sz;i++){
		x=i%w,y=i/w;
		ox=(ca*x-sa*y)*ratio+ddx,oy=(sa*x+ca*y)*ratio+ddy;
		oi=oy*w+ox;
		//printf("%ld,%ld:%ld\n",ox,oy,oi);
		//fflush(stdout);
		//getchar();
		if(oi<w*h&&oi>=0){
			fseek(p[1],ini+oi*3,SEEK_SET);
			fread(color,1,3,p[0]);
			fwrite(color,1,3,p[1]);
		}
	}
        fclose(p[0]);
        fclose(p[1]);
        return 0;
}
