all:poker.o data.o polycal.o banqi.o
	gcc hw0501.c poker.o -lm -o hw0501
	gcc hw0502.c data.o -lm -o hw0502
	gcc hw0503.c polycal.o -lm -o hw0503
	gcc hw0504.c banqi.o -lm -o hw0504
	gcc hw0505.c -lm -o hw0505
%.o:%.c
	gcc -c $< -o $@
clean:
	rm hw0501 hw0502 hw0503 hw0504 hw0505 *.o
