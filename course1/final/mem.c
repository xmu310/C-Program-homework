#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
void *my_malloc(size_t size,size_t front_size,size_t *available_front_size){
}
void my_push(void **ptr,size_t size,size_t *available_front_size){
}
void my_free(void *ptr,size_t available_front_size){
	free((int8_t*)ptr-available_front_size);
}
