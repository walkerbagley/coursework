# Author: Walker Bagley
# Email: wbagley@nd.edu

# This is the Makefile for Code Environment Setup Example

# CC is for the gcc compiler for C
CC := gcc

# CFLAGS are the required compiler flags for the CSE 20133 course
CFLAGS := -O2 -g -std=c11 -Wall -Wextra -Wconversion -Wshadow -lm -Werror
# Compilation for the nothing program
# Command: make nothing
nothing: nothing.o
	$(CC) $(CFLAGS) -o nothing nothing.o
#
nothing.o: nothing.c
	$(CC) $(CFLAGS) -c nothing.c


# Modified Hello for Lab 1
# Command: make modHello
modHello: modHello.o
	$(CC) $(CFLAGS) -o modHello modHello.o

modHello.o: modHello.c
	$(CC) $(CFLAGS) -c modHello.c


# Modified specifiers for Lab 1
# Command: make modPrint
modPrint: modPrint.o
	$(CC) $(CFLAGS) -o modPrint modPrint.o

modPrint.o: modPrint.c
	$(CC) $(CFLAGS) -c modPrint.c


# Compilation for printing Hello World with a string specifier
# Command: make specifiers
helloSpec: helloSpec.o
	$(CC) $(CFLAGS) -o helloSpec helloSpec.o

helloSpec.o: helloSpec.c
	$(CC) $(CFLAGS) -c helloSpec.c

# Make all
all: nothing modHello modPrint helloSpec

# Make clean
clean:
	rm -rf *.o *.swp nothing modHello modPrint helloSpec
