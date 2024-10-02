build: pa04.c test.o
	@echo Compiling project
	@gcc $< -o pa04.o -lgmp -lpbc -I/usr/local/include/include/pbc/

test.o: gradingPA04.c
	@echo Compiling test script
	@gcc $< -o $@ -lgmp -lpbc -I/usr/local/include/include/pbc/

test: test.o build
	@echo Running test script
	@./$<

clean:
	@echo Cleaning
	@rm -f *.o