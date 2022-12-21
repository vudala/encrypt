#!/bin/bash

CC=g++
FLAGS= -g --std=c++17
LIBS=
SRC=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRC))
OUTPUT=program
RM=rm -f

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUTPUT) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

encrypt:
	./$(OUTPUT) -k vintee9patinhosnumalagoasujadebosta -f ./input.txt

decrypt:
	./$(OUTPUT) -d -k vintee9patinhosnumalagoasujadebosta -f ./output.txt

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)