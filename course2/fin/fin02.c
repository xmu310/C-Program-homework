#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
int64_t legalday[12]={31,29,31,30,31,30,31,31,30,31,30,31},infect[3]={0},total;
char output[1000]="output.csv",country[1000]="Taiwan",c,cc,cmd[10000]={0},filename[1000]={0},tmp[1000];
int64_t month[3]={1,12,0},day[3]={23,31,0},year[3]={2020,2021,0};
void f(int i){
	if(sscanf(optarg,"%ld-%ld-%ld%c",&month[i],&day[i],&year[i],&cc)!=3||month[i]<1||month[i]>12||day[i]<1||day[i]>legalday[month[i]-1]||year[i]<2020||year[i]>2022||year[i]!=2020&&month[i]==2&&day[i]==29||year[i]==2020&&month[i]==1&&day[i]<22||year[i]==2022&&month[i]>=7||year[i]==2022&&month[i]==6&&day[i]>3){printf("Date syntax error or not exist in data.\n");exit(0);}
}
int main(int argc,char *argv[]){
	int help=0;
	struct option optl[]={
		{"country",0,0,'c'},
		{"start",0,0,'s'},
		{"end",0,0,'e'},
		{"output",0,0,'o'},
		{"help",0,&help,1},
		{0,0,0,0}
	};
	while((c=getopt_long(argc,argv,"c:s:e:o:",optl,0))!=-1){
		if(c=='c'){
			strcpy(country,optarg);
		}else if(c=='s'){
			f(0);
		}else if(c=='e'){
			f(1);
		}else if(c=='o'){
			strcpy(output,optarg);
		}else if(c!=0){
			printf("Syntax error!\n");
			return 0;
		}
	}
	if(argc-optind!=0){printf("Syntax error!\n");return 0;}
	if(year[1]<year[0]||year[1]==year[0]&&month[1]<month[0]||year[1]==year[0]&&month[1]==month[0]&&day[1]<day[0]){printf("End date is earlier than start date!");return 0;}
	if(help){
		printf("Usage:\n");
		printf("  ./fin01 [options]\n");
		printf("    -c: --country: the country name. default: Taiwan\n");
		printf("    -s: --start MM-DD-YYYY: the start date. default: 01-02-2020\n");
		printf("    -e: --end MM-DD-YYYY: the end date. default: 12-31-2021\n");
		printf("    -o: --output: output file name. default: output.csv\n");
		printf("    --help: This description\n");
		return 0;
	}
	month[2]=month[0],day[2]=day[0]-1,year[2]=year[0];
	FILE *ofp=fopen(output,"w+");
	fprintf(ofp,"Date, New infected\n");
	int64_t check=0,alln=0;
	infect[2]=0;
	while(1){
		snprintf(filename,1000,"%02ld-%02ld-%04ld.csv",month[2],day[2],year[2]);
		snprintf(cmd,10000,"wget -nv raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/%s -O %s",filename,filename);
		system(cmd);
		FILE *fp=fopen(filename,"r");
		char *p;
		if(!fp){printf("open %s failed!\n",filename);return 0;}
		while(1){
			if(fscanf(fp,"%[^\n]",tmp)!=1)break;
			fscanf(fp,"%*c");
			p=strpbrk(tmp,",");
			if(!p)break;
			p=strstr(tmp,country);
			if(p){
				int64_t tmpn;
				p=strpbrk(p,",");
				p++;
				p=strpbrk(p,",");
				p++;
				sscanf(p,"%ld",&tmpn);
				infect[1]+=tmpn;
			}
		}
		if(check)fprintf(ofp,"%02ld-%02ld-%02ld,%01ld\n",month[2],day[2],year[2],infect[1]-infect[0]);
		snprintf(cmd,10000,"rm %s",filename);
		system(cmd);
		if(check)infect[2]+=infect[1]-infect[0],alln++;
		infect[0]=infect[1];
		infect[1]=0;
		day[2]++;
		if(day[2]>legalday[month[2]]||year[2]!=2020&&month[2]==2&&day[2]==29)day[2]=1,month[2]++;
		if(month[2]>12)month[2]=1,year[2]++;
		if(year[1]<year[2]||year[1]==year[2]&&month[1]<month[2]||year[1]==year[2]&&month[1]==month[2]&&day[1]<day[2])break;
		check=1;
	}
	fprintf(ofp,"Average,%01ld\n",infect[2]/alln);
	return 0;
}
