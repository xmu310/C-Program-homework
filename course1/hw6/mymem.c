#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void my_realloc(void **pptr,size_t before,size_t after){
	if(after==0){
		free(*pptr);
		*pptr=NULL;
		return;
	}
	if(before<=after){
		int8_t *pb=*(int8_t**)pptr,*pa=calloc(after,1);
		for(size_t i=0;i<before;i++)*(pa+i)=*(pb+i);
		free(pb);
		*pptr=pa;
	}else{
		int64_t *ptr=*(int64_t**)pptr,*p=calloc(after,1);
		before=*(ptr-1)-17;
		after=*(p-1)-17;
		free(p);
		if(before-after>=32){
			*(ptr-1)=after+17;
			*(ptr+after/8+1)=before-after+1;
			free(ptr+after/8+2);
		}
	}
}
