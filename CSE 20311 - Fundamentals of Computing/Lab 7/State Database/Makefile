
states: usastates.o statefunc.o
	gcc statefunc.o usastates.o -o states

statefunc.o: statefunc.c statefunc.h
	gcc -c statefunc.c -o statefunc.o

usastates.o: usastates.c statefunc.h
	gcc -c usastates.c -o usastates.o

clean:
	rm *.o
	rm states

