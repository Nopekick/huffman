CC=g++

all: main

main: main.o decode.o encode.o
	$(CC) -o main main.o decode.o encode.o

main.o: decode.h encode.h main.cpp	
	$(CC) -c main.cpp

decode.o: decode.cpp decode.h
	$(CC) -c decode.cpp	

encode.o: encode.cpp encode.h
	$(CC) -c encode.cpp	

clean:
	rm -f main decode.o encode.o main.o