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
glm = ./Graphics/glm/glm/
angel = ./Graphics/angel/include/

# What compiler do you want to use for c++ files?
CC = g++

# Compiler options -g for debug info
GCC_OPTIONS= -pedantic -g 

# What libraries to link GLU is included for backwards compatibility
#LDLIBS = -lGL -lGLU /usr/lib/x86_64-linux-gnu/libglut.so.3 /usr/lib/x86_64-linux-gnu/libGLEWmx.so.1.13
LDLIBS = -lGL -lGLU  -lGLEW /usr/lib/x86_64-linux-gnu/libglut.so.3
#LDLIBS = -lGL -lGLU  -lGLEW -lGLUT

# program to link in compiling all binaries that initialize shaders
InitShader = /home/mcolvin/Desktop/othello/Graphics/angel/Common/InitShader.o

# Where to find the include files
INCS = -I /usr/include/ -I $(glm) -I $(angel) -I $(headerpth)

# options to pass to the compiler (all the gcc ones, and the where to
# find the includes).
OPTIONS=$(GCC_OPTIONS) $(INCS) -Wall -std=c++17

OBJECTS = $(patsubst %.cc,%,$(wildcard *.cc)) 

all: homework2

release: all clean

run: release
	./homework2

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

####################################################################

homework2: object.o    $(headerpth)object.h    \
		   cube.o      $(headerpth)cube.h      \
		   scene.o     $(headerpth)scene.h     \
		   sphere.o    $(headerpth)sphere.h    \
		   cube_door.o $(headerpth)cube_door.h \
		   camera.o    $(headerpth)camera.h    \
		   piece.o     $(headerpth)piece.h
	$(CC)  Homework2.cc object.o scene.o piece.o cube.o cube_door.o camera.o sphere.o $(InitShader) $(INCS) $(OPTIONS) $(LDLIBS) -o homework2
clean:
	rm -f $(OBJECTS) *.o *~
squeakyclean: clean
	rm -f homework2 