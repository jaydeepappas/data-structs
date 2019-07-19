a8: Assign08.o HashTable.o
	g++ Assign08.o HashTable.o -o a8
Assign08.o: Assign08.cpp HashTable.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign08.cpp
HashTable.o: HashTable.cpp HashTable.h
	g++ -Wall -ansi -pedantic -std=c++11 -c HashTable.cpp

clean:
	@rm -rf Assign08.o HashTable.o

cleanall:
	@rm -rf Assign08.o HashTable.o a8
