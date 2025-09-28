all: output

run: all
	bin/pa2.exe

output: obj/main.o obj/graph.o obj/list.o
	g++ -Wall -o bin/pa2.exe obj/main.o obj/graph.o obj/list.o

obj/main.o: src/main.cpp obj/graph.o
	g++ -Wall -Iinclude  -c src/main.cpp -o obj/main.o
	
obj/graph.o: src/graph.cpp include/graph.hpp
	g++ -Wall -Iinclude -c src/graph.cpp -o obj/graph.o

obj/list.o: src/list.cpp include/list.hpp
	g++ -Wall -Iinclude -c src/list.cpp -o obj/list.o

clean:
	rm -rf bin/*

clean_win:
	del /Q /S bin\* obj\*