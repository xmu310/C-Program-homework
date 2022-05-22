#include<stdio.h>
#include<stdlib.h>
#include"mystring.h"
int mystrsplit(char ***pppList,int *pCounter,const char *pStr,const char *pSeparator){
	char **str,*cur=(char*)pStr,*next,*sep=(char*)pSeparator;
	int n;
	if(!pppList||!pCounter||!pStr||sep&&!*sep){*pppList=NULL;return -1;}
	str=calloc(mystrlen(pStr)+1,sizeof(char*));
	if(pStr&&!*pStr&&!sep){*pppList=str;*pCounter=0;return 0;}
	cur+=sep?0:mystrspn(cur," \f\n\r\t\v");
	for(n=0;next=sep?mystrstr(cur,sep):mystrpbrk(cur," \f\n\r\t\v");n++){
		str[n]=(char*)calloc(next-cur+1,1);
		for(int i=0;i<next-cur;i++)*(str[n]+i)=*(cur+i);
		cur=sep?next+mystrlen(sep):next+mystrspn(next," \f\n\r\t\v");
	}
	if(sep||!sep&&mystrlen(cur)){
		str[n]=(char*)calloc(mystrlen(cur)+1,1);
		for(int i=0;i<mystrlen(cur);i++)*(str[n]+i)=*(cur+i);
	}else n--;
	*pppList=str,*pCounter=n+1;
	return 0;
}
