a3: Sequence.o Assign03.o
	g++ Sequence.o Assign03.o -o a3
Sequence.o: Sequence.cpp Sequence.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Sequence.cpp
Assign03.o: Assign03.cpp Sequence.cpp Sequence.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign03.cpp

clean:
	@rm -rf Sequence.o Assign03.o
cleanall:
	@rm -rf Sequence.o Assign03.o a3

