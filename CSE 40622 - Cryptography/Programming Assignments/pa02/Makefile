build: pa02.c test.o
	@echo Compiling project
	@gcc $< -o pa02.o -lgmp

test.o: gradingPA02-local.c
	@echo Compiling test script
	@gcc $< -o $@ -lgmp

test: test.o build
	@echo Running test script
	@./$<

clean:
	@echo Cleaning
	@rm -f *.o