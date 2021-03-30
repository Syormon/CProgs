xref: main.o tree.o getch.o
	gcc -o xref main.o tree.o getch.o -lm

run: xref
	xref

main.o: main.c xref.h
	gcc -c main.c

tree.o: tree.c xref.h
	gcc -c tree.c

getch.o: getch.c xref.h
	gcc -c getch.c


clean:
	rm *.o xref
