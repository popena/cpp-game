CC = g++
FLAGS = -Wall -Werror -O2
LIBS = -lSDL2 -lSDL2_image

all: main

main: main.o sprite.o player.o tileSprites.o tile.o map.o particle.o
	$(CC) main.o sprite.o player.o tileSprites.o tile.o map.o particle.o utils.h -o main $(FLAGS) $(LIBS)

main.o: main.cpp utils.h map.h player.h
	$(CC) -c main.cpp $(FLAGS)

tileSprites.o: tileSprites.cpp tileSprites.h sprite.h utils.h
	$(CC) -c tileSprites.cpp $(FLAGS)

tile.o: tile.cpp tile.h tileSprites.h utils.h map.h particle.h
	$(CC) -c tile.cpp $(FLAGS)

sprite.o: sprite.cpp sprite.h utils.h
	$(CC) -c sprite.cpp $(FLAGS)

player.o: player.cpp player.h sprite.h utils.h map.h
	$(CC) -c player.cpp $(FLAGS)

map.o: map.cpp map.h tile.h utils.h tileSprites.h
	$(CC) -c map.cpp $(FLAGS)

particle.o: particle.cpp particle.h utils.h sprite.h
	$(CC) -c particle.cpp $(FLAGS)

clean:
	rm -f *.o main


