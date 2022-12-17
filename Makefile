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
	./$(OUTPUT) < input.txt

decrypt:
	./$(OUTPUT) -d < input.txt

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)