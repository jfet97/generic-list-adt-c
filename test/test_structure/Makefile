# make -> compile all the binaries 
# make debug -> compile with debug symbol
# make dist -> compile with compiler optimizations
# make clean -> remove the binaries

CFLAGS += -std=c99 -Wall -pedantic
TARGET = main

debug: CFLAGS += -g
debug: clean all

dist: CFLAGS += -O3
dist: clean all

.PHONY: clean

all: $(TARGET)

main: ./main.c ../../liblist.a ../../list.h
	$(CC) $(CFLAGS) $^ -I ../../ -L ../../ -llist -o $@

clean: 
	-rm -f $(TARGET)
