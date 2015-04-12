all:
	g++ -std=c++11 main.cc -Wall -Wfatal-errors -o knikkers `sdl2-config --cflags --libs` -lSDL2_image

