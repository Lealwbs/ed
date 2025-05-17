all: output

run_win: output_win
	bin/pa3.exe

run: output 
	clear
	bin/pa3.out

output_win: bin obj obj/main.o obj/heap.o
	g++ -Iinclude -Wall obj/main.o obj/heap.o -o bin/pa3.exe

output: bin obj obj/main.o obj/heap.o
	g++ -Iinclude -Wall obj/main.o obj/heap.o -o bin/pa3.out

obj/main.o: src/main.cpp
	g++ -Iinclude -Wall -c src/main.cpp -o obj/main.o

obj/heap.o: src/heap.cpp include/heap.hpp | obj
	g++ -Iinclude -Wall -c src/heap.cpp -o obj/heap.o

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	rm -rf bin/* obj/*.o 
	
clean_win:
	del -f bin\* obj\*.o