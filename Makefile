# This sample Makefile allows you to make an OpenGL application
#
# To use this Makefile, you type:
#
#        make          -to compile all of the code for Homework 2
#        make run      -to compile and then run the program         
#      	 make release  -to compile just the binary for running the program
#		 make debug    -to keep all of the object files
#
# Assumes the following file exists in the proper place.
srcpth = ./Graphics/source/
headerpth = ./Graphics/headers/
angel = ./Graphics/angel/include/
gamelogicpth = ./GameLogic/
# What compiler do you want to use for c++ files?
CC = g++

# Compiler options -g for debug info
GCC_OPTIONS= -pedantic -g 

# What libraries to link GLU is included for backwards compatibility
#LDLIBS = -lGL -lGLU /usr/lib/x86_64-linux-gnu/libglut.so.3 /usr/lib/x86_64-linux-gnu/libGLEWmx.so.1.13
LDLIBS = -lGL -lGLU  -lGLEW /usr/lib/x86_64-linux-gnu/libglut.so.3
#LDLIBS = -lGL -lGLU  -lGLEW -lGLUT

# program to link in compiling all binaries that initialize shaders
InitShader = ./Graphics/angel/Common/InitShader.o

# Where to find the include files
INCS = -I /usr/include/ -I $(angel) -I $(headerpth) -I $(gamelogicpth)

# options to pass to the compiler (all the gcc ones, and the where to
# find the includes).
OPTIONS=$(GCC_OPTIONS) $(INCS) -Wall -std=c++17

OBJECTS = $(patsubst %.cc,%,$(wildcard *.cc)) 



all: Termobjs homework2

release: all clean

run: release
	./homework2


##############Terminal game make##########################

Termbuild:Termgame

Termobjs: game.o othello.o termspace.o

Termgame: main.o Termobjs
	g++ main.o game.o othello.o termspace.o -o game

main.o: $(gamelogicpth)main.cpp
	g++ -c $(gamelogicpth)main.cpp

game.o:	$(gamelogicpth)game.cpp $(gamelogicpth)game.h
	g++ -c $(gamelogicpth)game.cpp

othello.o: $(gamelogicpth)othello.cpp $(gamelogicpth)colors.h space.o
	g++ -c $(gamelogicpth)othello.cpp

termspace.o: $(gamelogicpth)space.h $(gamelogicpth)space.cpp
	g++ -c $(gamelogicpth)space.cpp -o termspace.o
	
###########################################################

################Start Graphic code compliation###########
camera.o: $(srcpth)camera.cc $(headerpth)camera.h
	$(CC) $(srcpth)camera.cc -c $(OPTIONS)
scene.o :$(srcpth)scene.cc $(headerpth)scene.h
	$(CC) $(srcpth)scene.cc -c $(OPTIONS)

############### In world Objects ######################

object.o: $(headerpth)object.h $(srcpth)object.cc
	$(CC) $(srcpth)object.cc -c $(OPTIONS)  

cube.o: $(headerpth)cube.h \
        $(srcpth)cube.cc   \
		object.o
	$(CC) $(srcpth)cube.cc -c $(INCS) $(OPTIONS)
cube_door.o:$(headerpth)cube_door.h \
			$(srcpth)cube_door.cc   \
			object.o
	$(CC) $(srcpth)cube_door.cc  -c $(INCS) $(OPTIONS)
sphere.o: $(headerpth)sphere.h \
		  $(srcpth)sphere.cc   \
		  object.o
	$(CC) $(srcpth)sphere.cc  -c  $(INCS) $(OPTIONS)
piece.o: $(headerpth)piece.h \
		  $(srcpth)piece.cc   \
		  object.o
	$(CC) $(srcpth)piece.cc  -c  $(INCS) $(OPTIONS)
space.o: $(headerpth)space.h \
		  $(srcpth)space.cc   \
		  object.o
	$(CC) $(srcpth)space.cc  -c  $(INCS) $(OPTIONS)
board.o: $(headerpth)board.h \
		  $(srcpth)board.cc   \
		  object.o
	$(CC) $(srcpth)board.cc  -c  $(INCS) $(OPTIONS)

####################################################################

homework2: object.o    $(headerpth)object.h    \
		   cube.o      $(headerpth)cube.h      \
		   scene.o     $(headerpth)scene.h     \
		   sphere.o    $(headerpth)sphere.h    \
		   cube_door.o $(headerpth)cube_door.h \
		   camera.o    $(headerpth)camera.h    \
		   piece.o     $(headerpth)piece.h     \
		   board.o     $(headerpth)board.h     \
		   space.o     $(headerpth)space.h
	$(CC)  Homework2.cc *.o $(InitShader) $(INCS) $(OPTIONS) $(LDLIBS) -o homework2
clean:
	rm -f $(OBJECTS) *.o *~
squeakyclean: clean
	rm -f homework2 game