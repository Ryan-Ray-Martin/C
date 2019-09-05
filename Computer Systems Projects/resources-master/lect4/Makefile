all:

e1: example1.c
	@echo re-compiling example1...
	gcc example1.c -o example1

e2: example2.c
	@echo re-compiling example2...
	gcc example2.c -o example2

run1: e1
	./example1

run2: e2
	./example2

clean:
	@echo cleaning up old executables
	rm example1
	rm example2
