all: bin bin/spl_data_center

bin/spl_data_center: bin/MemoryBlock.o bin/Main.o
	g++ bin/MemoryBlock.o bin/Main.o -o bin/spl_data_center

bin/MemoryBlock.o: src/MemoryBlock.cpp | bin
	g++ -g -Wall -std=c++11 -c -Iinclude src/MemoryBlock.cpp -o bin/MemoryBlock.o

bin/Main.o: src/Main.cpp | bin
	g++ -g -Wall -std=c++11 -c -Iinclude src/Main.cpp -o bin/Main.o

bin:
	mkdir -p bin

clean:
	rm -rf bin/* bin/spl_data_center