all: marcdown clean

marcdown: main.o Block.o
	g++ -o marcdown main.o Block.o

main.o: main.cc Block.h
	g++ -c main.cc

Block.o: Block.cc Block.h
	g++ -c Block.cc

clean:
	rm *.o

