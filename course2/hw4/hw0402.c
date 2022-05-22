#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char *argv[]){
	char opt,iname[1000]={0},sname[1000]="Test",sname_lc[1000]={0},oname[1000]="test",cname[2000]={0},hname[2000]={0};
	char smname[10000][100]={0},c;
	int64_t opt_i=0,opt_n=0,opt_p=0,smn=0,smlen[10000]={0},smblen[10000]={0},pre;
	FILE *ifp,*ofp;
	while(opt=getopt(argc,argv,"i:n:p:"),opt!=-1){
		if(opt=='i'&&!opt_i){opt_i=1;strncpy(iname,optarg,1000);}
		else if(opt=='n'&&!opt_n){opt_n=1;strncpy(sname,optarg,1000);}
		else if(opt=='p'&&!opt_p){opt_p=1;strncpy(oname,optarg,1000);}
		else{printf("Syntax error!\n");return 0;}
	}
	if(!opt_i){printf("-i is needed!\n");return 0;}
	if(argc-1!=(opt_i+opt_n+opt_p)*2){printf("Syntax error!\n");return 0;}
	ifp=fopen(iname,"r");
	if(!ifp){printf("open input file failed!\n");return 0;}
	strncpy(sname_lc,sname,1000);
	for(int i=0;i<strlen(sname_lc);i++)if(sname_lc[i]>='A'&&sname_lc[i]<='Z')sname_lc[i]|=' ';
	snprintf(hname,2000,"%s.h",oname);
	ofp=fopen(hname,"w+");
	fprintf(ofp,"#pragma once\n\n#include <stdint.h>\n\ntypedef struct _s%s\n{\n",sname);
	fscanf(ifp,"%*[^|]|");
	while(1){
		pre=ftell(ifp);
		if(fscanf(ifp," %[^|] |",smname[smn])!=1)break;
		if(smname[smn][0]=='+'){memset(smname[smn],0,100);continue;}
		for(int i=0;smname[smn][i];i++)if(smname[smn][i]==' ')for(int j=i;smname[smn][j];j++)smname[smn][j]=smname[smn][j+1];
		while(smname[smn][strlen(smname[smn])-1]==' ')smname[smn][strlen(smname[smn])-1]=0;
		for(int i=0;smname[smn][i];i++)if(smname[smn][i]>='A'&&smname[smn][i]<='Z')smname[smn][i]|=' ';
		smlen[smn]=(ftell(ifp)-pre)/2;
		if(!strcmp(smname[smn],smname[smn-1])){smlen[smn-1]+=smlen[smn];continue;}
		if(smlen[smn]==8||smlen[smn]==16||smlen[smn]==32||smlen[smn]==64){fprintf(ofp,"  uint%ld_t %s;\n",smlen[smn],smname[smn]);}
		else if(smlen[smn]<8){fprintf(ofp,"  uint8_t %s;\n",smname[smn]);}
		else if(smlen[smn]%8==0){fprintf(ofp,"  uint8_t %s[%ld];\n",smname[smn],smlen[smn]/8);}
		else if(smlen[smn]<16){fprintf(ofp,"  uint16_t %s;\n",smname[smn]);}
		else if(smlen[smn]<32){fprintf(ofp,"  uint32_t %s;\n",smname[smn]);}
		else if(smlen[smn]<64){fprintf(ofp,"  uint64_t %s;\n",smname[smn]);}
		smn++;
	}
	fclose(ifp);
	fprintf(ofp,"}%s;\n\n%s * %s_init( void );\nvoid %s_free( %s * );\n",sname,sname,sname_lc,sname_lc,sname);
	fprintf(ofp,"int %s_encode( void *, const %s * );\nint %s_decode( const void *, %s * );\n",sname_lc,sname,sname_lc,sname);
	fclose(ofp);
	snprintf(cname,2000,"%s.c",oname);
	ofp=fopen(cname,"w+");
	fprintf(ofp,"#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n#include\"%s\"\ntypedef struct {\n",hname);
	for(int i=0;i<smn;i++){
		if(smlen[i]==8||smlen[i]==16||smlen[i]==32||smlen[i]==64)fprintf(ofp,"  uint%ld_t %s;\n",smlen[i],smname[i]);
		else if(smlen[i]<8)fprintf(ofp,"  uint8_t %s:%ld;\n",smname[i],smlen[i]);
		else if(smlen[i]%8==0)fprintf(ofp,"  uint8_t %s[%ld];\n",smname[i],smlen[i]/8);
		else if(smlen[i]<16)fprintf(ofp,"  uint16_t %s:%ld;\n",smname[i],smlen[i]);
		else if(smlen[i]<32)fprintf(ofp,"  uint32_t %s:%ld;\n",smname[i],smlen[i]);
		else if(smlen[i]<64)fprintf(ofp,"  uint64_t %s:%ld;\n",smname[i],smlen[i]);
	}
	fprintf(ofp,"}__attribute__((packed))Smalls;\n");
	fprintf(ofp,"%s * %s_init( void ){return calloc(sizeof(%s),1);}\n",sname,sname_lc,sname);
	fprintf(ofp,"void %s_free( %s *sp ){if(!sp){printf(\"NULL POINTER!\\n\");return;};free(sp);}\n",sname_lc,sname);
	fprintf(ofp,"int %s_encode( void *p, const %s *sp ){\n",sname_lc,sname);
	fprintf(ofp,"	if(!p||!sp){printf(\"NULL POINTER!\\n\");return -1;}\n");
	fprintf(ofp,"	memset(p,0,sizeof(Smalls));\n");
	for(int i=0;i<smn;i++){
		if(smlen[i]>8&&smlen[i]!=16&&smlen[i]!=32&&smlen[i]!=64&&smlen[i]%8==0)fprintf(ofp,"	for(int i=0;i<%ld;i++)(*(Smalls*)p).%s[i]=(*(%s*)sp).%s[i];\n",smlen[i]/8,smname[i],sname,smname[i]);
		else fprintf(ofp,"	(*(Smalls*)p).%s=(*(%s*)sp).%s;\n",smname[i],sname,smname[i]);
	}
	fprintf(ofp,"	return 0;\n}\n");
	fprintf(ofp,"int %s_decode( const void *p, %s *sp ){\n",sname_lc,sname);
	fprintf(ofp,"	if(!p||!sp){printf(\"NULL POINTER!\\n\");return -1;}\n");
	fprintf(ofp,"	memset(sp,0,sizeof(%s));\n",sname);
	for(int i=0;i<smn;i++){
		if(smlen[i]>8&&smlen[i]!=16&&smlen[i]!=32&&smlen[i]!=64&&smlen[i]%8==0)fprintf(ofp,"	for(int i=0;i<%ld;i++){(*(%s*)sp).%s[i]=(*(Smalls*)p).%s[i];}\n",smlen[i]/8,sname,smname[i],smname[i]);
		else fprintf(ofp,"	(*(%s*)sp).%s=(*(Smalls*)p).%s;\n",sname,smname[i],smname[i]);
	}
	fprintf(ofp,"	return 0;\n}\n");
	fclose(ofp);
	return 0;
}
