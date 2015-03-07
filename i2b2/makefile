dei-train dei-predict: dei-train.o dei-predict.o svm.o
	g++ dei-train.o svm.o -o dei-train -g
	g++ dei-predict.o svm.o -o dei-predict -g

dei-train.o: dei-train.cpp
	g++ -c dei-train.cpp -g

dei-predict.o: dei-predict.cpp
	g++ -c dei-predict.cpp -g

svm.o: svm.cpp
	g++ -c svm.cpp -g

clean:
	rm *.o
