.IGNORE:all
all:mystring.o
	gcc mid01.c mystring.o -o mid01
	gcc mid02.c -lm -o mid02
	gcc mid03.c -lm -o mid03
	gcc mid04.c -lm -o mid04
%.o:%.c
	gcc -c $< -o $@
clean:
	rm mid01 mid02 mid03 mid04 *.o
	
