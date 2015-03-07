main: main.o graph.o traveler.o tree.o
	g++ main.o graph.o traveler.o tree.o -o main -g

main.o: main.cpp 
	g++ -c main.cpp -g

graph.o: graph.cpp 
	g++ -c graph.cpp -g

traveler.o: traveler.cpp
	g++ -c traveler.cpp -g

tree.o: tree.cpp
	g++ -c tree.cpp -g

clean:
	rm *.o
