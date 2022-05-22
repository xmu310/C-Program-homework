#include<string.h>
char *mystrtok_r(char *str,const char *delim,char **saveptr){
	char *cur,*next=*saveptr;
	cur=(str?str:next),cur+=strspn(cur,delim),next=cur+strcspn(cur,delim),*next=0,next++;
	*saveptr=next;
	return *cur?cur:NULL;
}
