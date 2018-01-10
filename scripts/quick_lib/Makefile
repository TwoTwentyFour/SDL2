OBJS = src/*.cpp
CC = g++
COMPILER_FLAGS = -Wall -std=gnu++11
OBJ_NAME = build/run

LINKER_FLAGS = 
ifeq ($(OS),Windows_NT)
	LINKER_FLAGS += -lmingw32 -lkernel32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
else
	LINKER_FLAGS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  
endif

INCLUDE_PATHS =
ifeq ($(OS),Windows_NT)
	INCLUDE_PATHS += -ID:\mingw_dev_lib\include\SDL2
endif

LIBRARY_PATHS = 
ifeq ($(OS),Windows_NT)
	LIBRARY_PATHS += -LD:\mingw_dev_lib\lib
endif

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


