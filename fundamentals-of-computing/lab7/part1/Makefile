
path: path.o pathfunc.o
	gcc pathfunc.o path.o -o path -lm

pathfunc.o: pathfunc.c pathfunc.h
	gcc -c pathfunc.c -o pathfunc.o -lm

path.o: path.c pathfunc.h
	gcc -c path.c -o path.o -lm

clean:
	rm *.o
	rm path

