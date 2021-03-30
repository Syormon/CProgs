calc: main.o getop.o getch.o stack.o
	cc -o calc main.o getop.o getch.o stack.o -lm

main.o: main.c calc.h
	cc -c main.c

getop.o: getop.c calc.h
	cc -c getop.c

getch.o: getch.c 
	cc -c getch.c

stack.o: stack.c
	cc -c stack.c

clean:
	rm *.o calc
