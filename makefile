CC=g++
CFLAGS=-std=c++11 -Wall
INC_DIR=./include
LIBS=-lGL -lGLEW -lm -lglfw -I/usr/include/freetype2 -I$(INC_DIR)

swordthrower: src/Main.cpp
	$(CC) $(CFLAGS) src/*.cpp $(LIBS) -o swordthrower
	mv swordthrower build/release/

clean:
	rm swordthrower
