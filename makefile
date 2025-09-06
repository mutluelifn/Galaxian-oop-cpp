exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses

asan: main.cpp
	g++ -g -fsanitize=address *.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out
