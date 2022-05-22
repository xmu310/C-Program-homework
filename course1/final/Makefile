all:go.o frac.o
	gcc fin01.c -lm -o fin01
	gcc fin02.c go.o -lm -o fin02
	gcc fin03.c frac.o -lm -o fin03
	gcc fin04.c -lm -o fin04
%.o:%.c
	gcc -c $< -o $@
clean:
	rm fin01 fin02 fin03 fin04 *.o

