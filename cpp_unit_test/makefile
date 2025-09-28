#  ╔═══════════════════════════════════════════════════════════════════════╗
#  ║ WINDOWS COMMANDS ●                                                    ║
#  ╚═══════════════════════════════════════════════════════════════════════╝

run: compile
	cls
	./bin/main.exe
	
compile: assert
	g++ -Iinclude ./src/main.cpp ./obj/assert.o -o ./bin/main.exe

assert:
	g++ -Iinclude -c ./src/assert.cpp -o ./obj/assert.o

clean:
	del bin\*.exe 
	del obj\*.o

#  ╔═══════════════════════════════════════════════════════════════════════╗
#  ║ LINUX COMMANDS ● Prefix lx* for linux                                 ║
#  ╚═══════════════════════════════════════════════════════════════════════╝

lxrun: lxcompile
	clear
	./bin/main.out

lxcompile: lxassert
	g++ -Iinclude -Wall ./src/main.cpp ./obj/assert.o -o ./bin/main.out

lxassert: 
	g++ -Iinclude -Wall -c ./src/assert.cpp -o ./obj/assert.o

lxclean:
	rm -rf bin/*.out bin/*.exe obj/*.o
