llcp: llcpImp.o Assign06P1.o
	g++ llcpImp.o Assign06P1.o -o a6p1
llcpImp.o: llcpImp.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c llcpImp.cpp
Assign06P1.o: Assign06P1.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign06P1.cpp

go:
	./a6p1
gogo:
	./a6p1 > a6p1test.out

clean:
	@rm -rf llcpImp.o Assign06P1.o
cleanall:
	@rm -rf llcpImp.o Assign06P1.o a6p1
