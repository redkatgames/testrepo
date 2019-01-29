

#comentariu
CC=g++
CFLAGS=-c -Wall

all: main

main: function1.o function2.o main.o
	$(CC) main.o function1.o function2.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
function1.o: function1.cpp
	$(CC) $(CFLAGS) function1.cpp

function2.o: function2.cpp
	$(CC) $(CFLAGS) function2.cpp
	
clean:
	rm -rf *o main
	
