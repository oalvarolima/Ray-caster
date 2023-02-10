#must have a build dir with this specification
#--+build
#	--+lights
#	--+objects
#		--+meshs
#	--+utils
CC=g++
SOURCES=$(wildcard source/*.cpp source/*/*.cpp source/*/*/*.cpp)
OBJS=$(SOURCES:source/%.cpp=build/%.o)
FLAGS=-Wall -pedantic -Wextra -O2 -ltbb
SDLFLAGS=`sdl2-config --cflags --libs` -lSDL2_image

all: build/main.o $(OBJS)
	$(CC) $^ $(FLAGS) -o main -lSDL2
	./main

build/main.o: main.cpp
	$(CC) -c $< $(FLAGS) $(SDLFLAGS) -o $@

build/%.o: source/%.cpp headers/%.hpp
	$(CC) -c $(FLAGS) $< -o  $@

clean:
	rm build/*.o build/*/*.o build/*/*/*.o main