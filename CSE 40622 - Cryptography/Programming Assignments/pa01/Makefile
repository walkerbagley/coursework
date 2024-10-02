build: pa01.c test.o
	@echo Compiling project
	@gcc $< -o pa01.o -lgmp

test.o: gradingPA01-local.c
	@echo Compiling test script
	@gcc $< -o $@ -lgmp

test: test.o build
	@echo Running test script
	@./$<

clean:
	@echo Cleaning
	@rm -f *.o