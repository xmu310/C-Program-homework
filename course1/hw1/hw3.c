#include<stdio.h>
#include<stdint.h>
int main()
{
	uint16_t a,b;
	printf("Please enter an unsigned 16-bits number: ");
	scanf("%hu",&a);
	printf("Before Flip:\n");
	printf("%hu_10 = %04x_16\n",a,a);
	printf("After  Flip:\n");
	b=(a>>12&0x000f)+(a>>4&0x00f0)+(a<<4&0x0f00)+(a<<12&0xf000);
	printf("%hu_10 = %04x_16\n",b,b);
	return 0;
}
