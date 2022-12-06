mine: minesweeper.o minefunc.o
	gcc minefunc.o minesweeper.o gfx2.o -lX11 -lm -o mine

minefunc.o: minefunc.c minefunc.h
	gcc -c minefunc.c gfx2.o -lX11 -lm -o minefunc.o

minesweeper.o: minesweeper.c minefunc.h
	gcc -c minesweeper.c gfx2.o -lX11 -lm -o minesweeper.o

clean:
	rm minesweeper.o
	rm minefunc.o
	rm mine
