.IGNORE:all
all:
	gcc fin01.c -lm -o fin01
	gcc fin02.c -lm -o fin02
	gcc fin03.c -lm -o fin03
%.o:%.c
	gcc -c $< -o $@
clean:
	rm -f fin01 fin02 fin03 *.o
	
