all: compile run

.PHONY : compile clear clean networktictactoe tictactoe link commit
compile: clear clean tictactoe networktictactoe link

clear:
	clear

clean:
	rm -f *.o

networktictactoe: networktictactoe.cpp
	gcc -c networktictactoe.cpp -Wall

tictactoe: tictactoe.cpp
	gcc -c tictactoe.cpp -Wall

link:
	g++ -o a networktictactoe.o tictactoe.o -Wall

run:
	./a 127.0.0.1 20000

commit:
	git commit -m
