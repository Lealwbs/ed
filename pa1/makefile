all: src/pa1
	
src/pa1: src/evalenum.c
	gcc src/evalenum.c -o bin/pa1.out
	
run: all
	clear
	./bin/pa1.out

clean:
	rm -rf bin/*
	clear
