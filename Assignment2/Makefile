a2: IntSet.o Assign02.o
	g++ IntSet.o Assign02.o -o a2
IntSet.o: IntSet.cpp IntSet.h
	g++ -Wall -ansi -pedantic -std=c++11 -c IntSet.cpp
Assign02.o: Assign02.cpp IntSet.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign02.cpp

cleanall:
	@rm a2 *.o
test:
	./a2 auto < a2test.in > a2test.out
