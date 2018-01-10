@echo off
cls


g++ %1% -std=c++0x  -o run_win32 -Wall -g -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image
