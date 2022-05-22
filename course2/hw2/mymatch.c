#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int mystrsplit(char ***pppList,int *pCounter,const char *pStr,const char *pSeparator){
        char **str,*cur=(char*)pStr,*next,*sep=(char*)pSeparator;
        int n;
        if(!pppList||!pCounter||!pStr||sep&&!*sep){*pppList=NULL;return -1;}
        str=calloc(strlen(pStr)+1,sizeof(char*));
        if(pStr&&!*pStr&&!sep){*pppList=str;*pCounter=0;return 0;}
        cur+=sep?0:strspn(cur," \f\n\r\t\v");
        for(n=0;next=sep?strstr(cur,sep):strpbrk(cur," \f\n\r\t\v");n++){
                str[n]=(char*)calloc(next-cur+1,1);
                for(int i=0;i<next-cur;i++)*(str[n]+i)=*(cur+i);
                cur=sep?next+strlen(sep):next+strspn(next," \f\n\r\t\v");
        }
        if(sep||!sep&&strlen(cur)){
                str[n]=(char*)calloc(strlen(cur)+1,1);
                for(int i=0;i<strlen(cur);i++)*(str[n]+i)=*(cur+i);
        }else n--;
        *pppList=str,*pCounter=n+1;
        return 0;
}
int f(const char *s,const char *pat){
	if(!*s){
		if(!*pat)return 1;
		if(*pat!='*')return 0;else f(s,pat+1);
	}
	if(!*pat)return 0;
	if(*s==*pat||*pat=='?')return f(s+1,pat+1);
	if(*pat=='*'){
		for(int i=0;i<strlen(s)+1;i++)if(f(s+i,pat+1))return 1;
		return 0;
	}
	return 0;
}
int mymatch(char ***pppList,const char *pStr,const char *pPattern){
	if(!pppList||!pStr||!pPattern||!*pPattern){*pppList=NULL;return -1;}
	char **ppList=calloc(3000,sizeof(char*)),**pp,pat[5000],*ppat=pat,t;
	strncpy(pat,pPattern,5000);
	int all,index=0;
	mystrsplit(&pp,&all,pStr," ");
	while(*ppat){
                if(*ppat=='*'){
                        if(*(ppat+1)=='*')for(int i=0;*(ppat+i);i++)*(ppat+i)=*(ppat+i+1);
			else if(*(ppat+1)=='?')t=*ppat,*ppat=*(ppat+1),*(ppat+1)=t,ppat++;
			else ppat++;
                }else ppat++;
        }
	for(int i=0;i<all;i++)if(f(pp[i],pat))ppList[index]=pp[i],index++;
	*pppList=ppList;
	return index;
}
