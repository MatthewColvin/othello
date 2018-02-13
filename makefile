all:clean archive build

build:game

game: main.o game.o othello.o space.o
	g++ main.o game.o othello.o space.o -o game

main.o: main.cpp
	g++ -c main.cpp

game.o:	game.cpp game.h
	g++ -c game.cpp

othello.o: othello.cpp colors.h space.o
	g++ -c othello.cpp

space.o: space.h space.cpp
	g++ -c space.cpp

clean:
	rm -rf *.o game *.tar.gz

archive:
	mkdir TMP
	cp *.* TMP
	tar -zcvf Othello_Archive.tar.gz TMP
	rm -r TMP
	
	
