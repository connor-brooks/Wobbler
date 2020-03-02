CC=g++

all: main

CFLAGS=-g3
LIBS=-lGLU -lSDL2 -lpthread -lSDL2_ttf

main: maximilian.o synth.o control.o voice.o gui_container.o utils.o init.o keyboard.o midi.o main.o 
	g++ -std=c++11 maximilian.o synth.o control.o voice.o gui_container.o utils.o init.o keyboard.o midi.o main.o -o wob -I /usr/local/Cellar/sdl2/2.0.10/include -L /usr/local/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 -lrtmidi -framework OpenGL

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

maximilian.o: ./libs/maximilian.cpp
	$(CC) -std=c++11 -c ./libs/maximilian.cpp

synth.o: synth.cpp
	$(CC) -std=c++11 -c synth.cpp

control.o: control.cpp
	$(CC) -std=c++11 -c control.cpp

voice.o: voice.cpp
	$(CC) -std=c++11 -c voice.cpp

gui_container.o: gui_container.cpp
	$(CC) -std=c++11 -c gui_container.cpp

utils.o: utils.cpp
	$(CC) -std=c++11 -c utils.cpp

init.o: init.cpp
	$(CC) -std=c++11 -c init.cpp

keyboard.o: keyboard.cpp
	$(CC) -std=c++11 -c keyboard.cpp

midi.o: midi.cpp
	$(CC) -std=c++11 -c midi.cpp

clean:
	rm *.o
	rm wob
