# Makefile, versao 1
# Analise e Sintese de Algoritmos

CC   = g++
LD   = g++
CFLAGS =-std=c++11 -O3 -Wall
LDFLAGS=-lm

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean run

all: main

main: main.o
	$(LD) $(CFLAGS) $(LDFLAGS) -o main main.o

#fs/state.o: fs/state.c fs/state.h tecnicofs-api-constants.h
#	$(CC) $(CFLAGS) -o fs/state.o -c fs/state.c

#fs/operations.o: fs/operations.c fs/operations.h fs/state.h tecnicofs-api-constants.h
#	$(CC) $(CFLAGS) -o fs/operations.o -c fs/operations.c

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp

clean:
	@echo Cleaning...
	rm -f *.o *.txt *.out main

run: main
	./main
