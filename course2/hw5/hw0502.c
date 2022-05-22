#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#define f(x) do{printf(x);return 0;}while(0)
#define im(x) uint8_t x[n##x]
#define openchk(x) do{fp=fopen(x,"r+");if(!fp)printf("%s: Open failed!\n",x);}while(0)
#define pf(name,mem) do{printf("  %s: %.*s\n",name,(int)n##mem,u.c28.mem);fflush(stdout);}while(0)
#define fif(x,y) do{if(opt==y){\
	if(narg>n##x){printf("String length (%ld) beyond max length (%ld)!\n",narg,n##x);return 0;}\
	if(!check){printf("%s: No TAG! -> Generate TAG\n",argv[i]);memset(&u,0,hsz);strcpy(u.c28.h,"TAG");*u.c28.g=255;}\
	strncpy(u.c28.x,arg,n##x);\
	fseek(fp,check?-hsz:0,SEEK_END);\
	fwrite(&u,hsz,1,fp);\
}}while(0)
int main(int argc,char *argv[]){
	FILE *fp;
	int64_t sz,check,nh=3,nt=30,na=30,nA=30,ny=4,nc28=28,nc30=30,nz=1,nT=1,ng=1,narg,hsz=128,year,ngenre=100,nc,track;
	char c,c2[2]={0},*endp,opt=0,*arg=NULL,tmp[1000];
	char *genre[80]={"Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge","Hip-Hop","Jazz","Metal",
		"New Age","Oldies","Other","Pop","Rhythm and Blues","Rap","Reggae","Rock","Techno","Industrial",
		"Alternative","Ska","Death Metal","Pranks","Soundtrack","Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz & Funk",
		"Fusion","Trance","Classical","Instrumental","Acid","House","Game","Sound clip","Gospel","Noise",
		"Alternative Rock","Bass","Soul","Punk","Space","Meditative","Instrumental Pop","Instrumental Rock","Ethnic","Gothic",
		"Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance","Dream","Southern Rock","Comedy","Cult","Gangsta",
		"Top 40","Christian Rap","Pop/Funk","Jungle music","Native US","Cabaret","New Wave","Psychedelic","Rave","Showtunes",
		"Trailer","Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical","Rock 'n' Roll","Hard Rock"
	};
	union{
		struct{im(h);im(t);im(a);im(A);im(y);im(c28);im(z);im(T);im(g);}c28;
		struct{im(h);im(t);im(a);im(A);im(y);im(c30);im(g);}c30;
	}u;
	while((c2[0]=getopt(argc,argv,"t:T:a:A:y:c:g:dlh"))!=-1){
		if(!opt&&strspn(c2,"tTaAycg")){opt=c2[0];arg=strdup(optarg);continue;}
		if(!opt&&strspn(c2,"dlh")){opt=c2[0];continue;}
		f("Syntax error!\n");
	}
	if(!opt||opt=='h'&&optind!=argc||opt!='h'&&optind==argc)f("Syntax error!\n");
	if(arg)narg=strlen(arg);
	if(opt=='h'){
		openchk("help2.txt");
		while(fp){c=getc(fp);if(!feof(fp))putchar(c);else break;}
		if(fp)fclose(fp);
		return 0;
	}else if(opt=='y'){
		year=strtol(arg,&endp,10);
		if(*endp)f("Not interger!\n");
		if(year<0||year>9999)f("Year should be 0-9999.\n");
		snprintf(tmp,1000,"%04ld",year);
		arg=strdup(tmp);
		narg=strlen(arg);
	}else if(opt=='g'){
		for(int i=0;i<80;i++)if(!strcmp(genre[i],arg)){ngenre=i;break;}
		if(ngenre==100)f("No this genre\n");
	}else if(opt=='T'){
		track=strtol(arg,&endp,10);
		if(*endp)f("Not interger!\n");
		if(track<0||track>255)f("Track should be 0-255.\n");
	}
	for(int i=optind;i<argc;i++){
		openchk(argv[i]);
		if(!fp)continue;
		fseek(fp,0,SEEK_END);
		sz=ftell(fp);
		fseek(fp,-hsz,SEEK_END);
		fread(&u,hsz,1,fp);
		check=!strncmp(u.c28.h,"TAG",3);
		if(opt=='l'){
			printf("%s:\n",argv[i]);
			if(!check){printf("No TAG!\n");continue;}
			pf("Title  ",t);pf("Artist",a);pf("Album  ",A);pf("Year",y);
			printf("  Genre: %s (%hhu)\n",*u.c28.g<80?genre[*u.c28.g]:(*u.c28.g==255?"undefined":"Error!"),*u.c28.g);
			if(!*u.c28.z){pf("Comment",c28);printf("  Track: %hhu\n",*u.c28.T);}
			if(*u.c28.z){printf("  Comment: %.30s\n",u.c30.c30);printf("  Track: (invalid)\n");}
		}else if(opt=='d'){
			if(!check){printf("%s: It doesn't have TAG before!\n",argv[i]);continue;}
			fclose(fp);
			if(truncate(argv[i],sz-hsz))printf("%s: Delete Tag failed!\n",argv[i]);
			continue;
		}else if(opt=='g'){
			if(!check){printf("%s: No TAG! -> Generate TAG\n",argv[i]);memset(&u,0,hsz);strcpy(u.c28.h,"TAG");}
			*u.c28.g=ngenre;
			fseek(fp,check?-hsz:0,SEEK_END);
			fwrite(&u,hsz,1,fp);
		}else if(opt=='c'){
			if(*u.c28.T&&!*u.c28.z)nc=28;else nc=30;
			if(narg>nc){printf("String length (%ld) beyond max length (%ld)!\n",narg,nc);continue;}
			if(!check){printf("%s: No TAG! -> Generate TAG\n",argv[i]);memset(&u,0,hsz);strcpy(u.c28.h,"TAG");*u.c28.g=255;}
			if(nc=28)strncpy(u.c28.c28,arg,nc28);
			if(nc=30)strncpy(u.c30.c30,arg,nc30);
			fseek(fp,check?-hsz:0,SEEK_END);
			fwrite(&u,hsz,1,fp);
		}else if(opt=='T'){
			if(*u.c28.z){printf("Zero-byte is not zero!\n");continue;}
			if(!check){printf("%s: No TAG! -> Generate TAG\n",argv[i]);memset(&u,0,hsz);strcpy(u.c28.h,"TAG");*u.c28.g=255;}
			*u.c28.T=track;
			fseek(fp,check?-hsz:0,SEEK_END);
			fwrite(&u,hsz,1,fp);
		}
		fif(t,'t');fif(a,'a');fif(A,'A');fif(y,'y');
		fclose(fp);
	}
	return 0;
}
