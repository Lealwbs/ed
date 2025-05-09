all: output

run_win: output_win
	clear
	bin/pa3.exe

run: output 
	clear
	bin/pa3.out

output_win:
	g++ -Iinclude -Wall obj/main.o obj/heap.o -o bin/pa3.exe

output: obj/main.o obj/heap.o
	g++ -Iinclude -Wall obj/main.o obj/heap.o -o bin/pa3.out

obj/main.o: src/main.cpp
	g++ -Iinclude -Wall -c src/main.cpp -o obj/main.o

obj/heap.o: src/heap.cpp include/heap.hpp
	g++ -Iinclude -Wall -c src/heap.cpp -o obj/heap.o

clean:
	rm -rf bin/* obj/*.o 
	
clean_win:
	del -f bin\* obj\*.o