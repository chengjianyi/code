dei-train dei-test: dei-train.o dei-test.o svm.o
	g++ dei-train.o svm.o -o dei-train -g
	g++ dei-test.o svm.o -o dei-test -g

dei-train.o: dei-train.cpp
	g++ -c dei-train.cpp -g

dei-test.o: dei-test.cpp
	g++ -c dei-test.cpp -g

svm.o: svm.cpp
	g++ -c svm.cpp -g

clean:
	rm *.o
