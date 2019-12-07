CC=g++
CFLAGS=-std=c++11 -Wall
INC_DIR=./include
LIBS=-lGL -lGLEW -lm -lglfw -lfreetype -lIrrKlang -I/$(INC_DIR)/freetype -I$(INC_DIR)

swordthrower: src/Main.cpp
	$(CC) $(CFLAGS) src/*.cpp $(LIBS) -o swordthrower
	mv swordthrower build/release/

install:
	cp ./dlls/libIrrKlang.so /usr/lib/

clean:
	rm swordthrower
