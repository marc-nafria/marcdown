all: marcdown clean

marcdown: main.o Block.o colors.o
	g++ -o marcdown main.o Block.o

main.o: main.cc Block.h
	g++ -c main.cc

Block.o: Block.cc Block.h colors.h
	g++ -c Block.cc

colors.o: colors.cc colors.h
	g++ -c colors.cc

clean:
	rm *.o

