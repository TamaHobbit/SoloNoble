FLAGS=-std=c++1z -Wall -Wfatal-errors `sdl2-config --cflags --libs` -lSDL2_image -pthread

solonoble: main.cc *.h
	clang++ $(FLAGS) main.cc -o $@

solonoble.html:
	em++ $(FLAGS) main.cc -o $@
