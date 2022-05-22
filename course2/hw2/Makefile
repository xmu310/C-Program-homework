.IGNORE:all
all:mymatch.o madoka.o myfrac.o myvector.o
	gcc hw0201.c mymatch.o -o hw0201
	gcc hw0202.c -o hw0202
	gcc hw0203.c madoka.o -o hw0203
	gcc hw0204.c myfrac.o -o hw0204
	gcc hw0205.c myvector.o -lm -o hw0205
	gcc hw0206.c -o hw0206
%.o:%.c
	gcc -c $< -o $@
clean:
	rm hw0201 hw0202 hw0203 hw0204 hw0205 hw0206 *.o

