all: compile run

.PHONY : compile clear clean kyle_bostian_prog1 tictactoe link commit
compile: clear clean tictactoe kyle_bostian_prog1 link

clear:
	clear

clean:
	rm -f *.o

kyle_bostian_prog1: kyle_bostian_prog1.cpp
	gcc -c kyle_bostian_prog1.cpp -Wall

tictactoe: tictactoe.cpp
	gcc -c tictactoe.cpp -Wall

link:
	g++ -o a kyle_bostian_prog1.o tictactoe.o -Wall

run:
	./a 127.0.0.1 10000

