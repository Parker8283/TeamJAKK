CC=g++
CFLAGS=-std=c++11 -Wall
INC_DIR=./include
LIBS=-lGL -lGLEW -lm -lglfw -lfreetype -I/usr/include/freetype2 -I$(INC_DIR)

swordthrower: Main.cpp
	$(CC) $(CFLAGS) Main.cpp src/*.cpp $(LIBS) -o swordthrower

clean:
	rm swordthrower
