all: marcdown clean

marcdown: main.o Block.o colors.o
	g++ -o marcdown main.o Block.o colors.o

main.o: source/main.cc source/headers/Block.h
	g++ -c source/main.cc -I source/headers/

Block.o: source/Block.cc source/headers/Block.h source/headers/colors.h
	g++ -c source/Block.cc -I source/headers/

colors.o: source/colors.cc source/headers/colors.h
	g++ -c source/colors.cc -I source/headers/

clean:
	rm *.o

