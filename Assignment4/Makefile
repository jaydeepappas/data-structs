a4: sequenceTest.o
	g++ sequenceTest.o -o a4
sequenceTest.o: sequenceTest.cpp sequence.template sequence.h
	g++ -Wall -ansi -pedantic -std=c++11 -c sequenceTest.cpp

test:
	./a4 auto < a4test.in > a4test.out
clean:
	@rm -rf sequenceTest.o
cleanall:
	@rm -rf sequenceTest.o a4

