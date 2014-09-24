# Makefile
#

CC = g++
SH = bash
CFLAGS = -g
LDFLAGS = -lm


all: tsp

# channel: channel.o main.o
# 	gcc $(LDFLAGS) $^ -o $@

# channel.o: channel.c channel.h
# 	gcc -c $(CFLAGS) $< -o $@

# main.o: main.c channel.h
# 	gcc -c $(CFLAGS) $< -o $@

tsp: main.o
	g++ $(LDFLAGS) $^ -o $@

main.o: main.cpp 
	g++ -c $(CFLAGS) $< -o $@

.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf tests/*_
	rm -rf tsp

lint:

test: all
	$(SH) tests/run_tests.sh

