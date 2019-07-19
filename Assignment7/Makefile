a7: Assign07Test.o DPQueue.o
	g++ Assign07Test.o DPQueue.o -o a7
Assign07Test.o: Assign07Test.cpp DPQueue.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign07Test.cpp
DPQueue.o: DPQueue.cpp DPQueue.h
	g++ -Wall -ansi -pedantic -std=c++11 -c DPQueue.cpp

clean:
	@rm -rf Assign07Test.o DPQueue.o

cleanall:
	@rm -rf Assign07Test.o DPQueue.o a7
