OBJS = Mandelbrot.cpp shader.cpp gameloop.cpp
CC = g++ -std=c++11
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJ_NAME = main
INC_DIRS = -I../Libraries -I../Libraries/glm

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INC_DIRS) -o $(OBJ_NAME)
