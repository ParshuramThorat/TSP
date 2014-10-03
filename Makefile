# Makefile
#

CC = g++
SH = bash
CFLAGS = -g
LDFLAGS = -lm


all: tsp

tsp: tsp.o main.o
	g++ $(LDFLAGS) $^ -o $@

tsp.o: TSP.cpp TSP.h
	g++ -c $(CFLAGS) $< -o $@

main.o: main.cpp TSP.h
	g++ -c $(CFLAGS) $< -o $@

.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf tests/*_
	rm -rf tsp

lint:

test: all
	$(SH) tests/run_tests.sh

