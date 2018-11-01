SERVER=server
CLIENT=client
GCC=gcc
GCC_OPTS=-std=c99 -Wall

.PHONY: all
all: bin/$(SERVER) bin/$(CLIENT)

bin/$(SERVER): src/$(SERVER).c
	$(GCC) $(GCC_OPTS) -o $@ $<

bin/$(CLIENT): src/$(CLIENT).c
	$(GCC) $(GCC_OPTS) -o $@ $<

.PHONY: clean
clean:
	rm -f bin/*
