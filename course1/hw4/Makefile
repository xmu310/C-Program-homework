all:k.o hanoi1.o hanoi2.o triangle.o er.o
	gcc hw0401.c k.o -lm -o hw0401
	gcc hw0402-1.c hanoi1.o -lm -o hw0402-1
	gcc hw0402-2.c hanoi2.o -lm -o hw0402-2
	gcc hw0403.c triangle.o -lm -o hw0403
	gcc hw0404.c er.o -lm -o hw0404
	gcc hw0405.c -lm -o hw0405
%.o:%.c
	gcc -c $< -o $@
clean:
	rm hw0401 hw0402-1 hw0402-2 hw0403 hw0404 hw0405 *.o
