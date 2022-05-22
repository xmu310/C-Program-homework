all:mirror.o ext.o mymem.o
	gcc hw0601.c mirror.o -lm -o hw0601
	gcc hw0602.c ext.o -lm -o hw0602
	gcc hw0603.c -lm -o hw0603
	gcc hw0604.c -lm -o hw0604
	gcc hw0605.c mymem.o -lm -o hw0605
	gcc hw0606.c -lm -o hw0606
%.o:%.c
	gcc -c $< -o $@
clean:
	rm hw0601 hw0602 hw0603 hw0604 hw0605 hw0606 *.o

