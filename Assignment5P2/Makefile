a5p2: Assign05P2.o cnPtrQueue.o nodes_LLoLL.o
	g++ Assign05P2.o cnPtrQueue.o nodes_LLoLL.o -o a5p2
Assign05P2.o: Assign05P2.cpp nodes_LLoLL.cpp nodes_LLoLL.h\
              cnPtrQueue.cpp cnPtrQueue.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign05P2.cpp
cnPtrQueue.o: cnPtrQueue.cpp cnPtrQueue.h  nodes_LLoLL.h
	g++ -Wall -ansi -pedantic -std=c++11 -c cnPtrQueue.cpp
nodes_LLoLL.o: nodes_LLoLL.cpp nodes_LLoLL.h
	g++ -Wall -ansi -pedantic -std=c++11 -c nodes_LLoLL.cpp
test:
	./a5p2 auto < a5p2_test.in > a5p2_test.out
clean:
	@rm -rf Assign05P2.o cnPtrQueue.o nodes_LLoLL.o
cleanall:
	@rm -rf Assign05P2.o cnPtrQueue.o nodes_LLoLL.o a5p2

