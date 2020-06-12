CC=g++

all: main

main: main.o decode.o encode.o
	$(CC) -o main main.o decode.o encode.o

main.o: decode.h encode.h main.cpp	
	$(CC) -c main.cpp

decode.o: decode.cpp decode.h node.h
	$(CC) -c decode.cpp	

encode.o: encode.cpp encode.h node.h
	$(CC) -c encode.cpp	

clean:
	rm -f main decode.o encode.o main.o

clear:
	rm -f test/output1 test/output2 test/decode1 test/decode2

tests: test-1 test-2

test-1:
	./main -e test/input1 test/output1	
	./main -d test/output1 test/decode1

test-2:
	./main -e test/input2 test/output2	
	./main -d test/output2 test/decode2