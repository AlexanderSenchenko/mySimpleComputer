all: bin/memory

bin/memory: build/main.o lib/libmemory.a
	gcc -Wall build/main.o lib/libmemory.a -o bin/memory

build/main.o: src/main.c src/memory.h
	gcc -Wall -c src/main.c -o build/main.o

lib/libmemory.a: build/memory.o
	ar rcs lib/libmemory.a build/memory.o

build/memory.o: src/memory.c src/memory.h
	gcc -Wall -c src/memory.c -o build/memory.o

.PHONY: clean
clean:
	rm -rf build/*.o
