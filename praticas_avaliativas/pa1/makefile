all: output

run_win: output_win
	cls
	./bin/pa1.exe

run: output
	clear
	./bin/pa1.out
	
output_win: src/evalenum.c bin
	gcc src/evalenum.c -o bin/pa1.exe
	
output: src/evalenum.c bin_
	gcc src/evalenum.c -o bin/pa1.out
	
bin:
	mkdir bin

clean:
	rm -rf bin/* obj/*.o 

clean_win:
	del -f bin\* obj\*.o