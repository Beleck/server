SERVER=server
CLIENT=client
INC=include
GCC=gcc
GCC_OPTS=-std=c99 -Wall

.PHONY: all
all: bin/$(SERVER) bin/$(CLIENT)

bin/$(SERVER): bin/$(SERVER).o bin/lib.o
	$(GCC) $(GCC_OPTS) -o $@ $^

bin/$(CLIENT): bin/$(CLIENT).o bin/lib.o
	$(GCC) $(GCC_OPTS) -o $@ $^

bin/%.o: src/%.c include/lib.h
	$(GCC) $(GCC_OPTS) -I./include/ -c $< -o $@

.PHONY: clean
clean:
	rm -f bin/*
