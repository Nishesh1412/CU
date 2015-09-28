EXPENDABLES = question15.o question15 bintree.o 

all:
	@make $(EXPENDABLES)

bintree.o: bintree.cpp bintree.h
	g++ -Wall -std=c++0x -g -c bintree.cpp -o bintree.o

# this compiles your test program and your binary_search_tree classes together
question15: question15.o binary_search_tree.o bintree.o
	g++ -Wall -std=c++0x -g question15.o bintree.o binary_search_tree.o -o question15

question15.o: binary_search_tree.h binary_search_tree.o bintree.h question15.cpp
	g++ -Wall -std=c++0x -g -c question15.cpp -o question15.o

# this deletes all the output files
clean:
	rm $(EXPENDABLES)
