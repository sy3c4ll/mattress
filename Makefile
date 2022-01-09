CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -O3 -g

demo: mattress.o demo.o
	if [ ! -d build ]; then mkdir build; fi
	$(CC) $(CFLAGS) -o build/demo build/mattress.o build/demo.o

mattress.o:
	if [ ! -d build ]; then mkdir build; fi
	$(CC) $(CFLAGS) -c -o build/mattress.o src/mattress.cpp

demo.o:
	if [ ! -d build ]; then mkdir build; fi
	$(CC) $(CFLAGS) -c -o build/demo.o src/demo.cpp

clean:
	rm -rf build

