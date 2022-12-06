crossword: crossword.o cwfunc.o
	gcc cwfunc.o crossword.o -o crossword

cwfunc.o: cwfunc.c cwfunc.h
	gcc -c cwfunc.c -o cwfunc.o

crossword.o: crossword.c cwfunc.h
	gcc -c crossword.c -o crossword.o

clean:
	rm *.o
	rm crossword