output: main.o game.o othello.o space.o
	g++ main.o game.o othello.o space.o -o output

main.o: main.cpp
	g++ -c main.cpp

game.o:	game.cpp game.h
	g++ -c game.cpp

othello.o: othello.cpp colors.h space.o
	g++ -c othello.cpp

space.o: space.h space.cpp
	g++ -c space.cpp

clean:
	rm *.o output

