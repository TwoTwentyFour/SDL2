clear
g++ -g -std=c++11 -Wall -o run_lx -cpp src/*.cpp `sdl2-config --cflags --libs` -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
