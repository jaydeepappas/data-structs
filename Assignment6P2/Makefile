a6p2: btNode.o Assign06P2.o
	g++ btNode.o Assign06P2.o -o a6p2
btNode.o: btNode.cpp btNode.h
	g++ -Wall -ansi -pedantic -std=c++11 -c btNode.cpp
Assign06P2.o: Assign06P2.cpp btNode.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign06P2.cpp

go:
	./a6p2
gogo:
	./a6p2 > a6p2.out
nt:
	@rm -rf *.h *.cpp *o *.out a6p2
clean:
	@rm -rf btNode.o Assign06P2.o
cleanall:
	@rm -rf btNode.o Assign06P2.o a6p2
