CC=gcc
CFLAGS=-I../ptlib/include -fopenmp
LDFLAGS=-lpt -lm
DEPS = dynarr.h
OBJ = dynarr.o ptlib-test.o

default: ptlib-test

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ptlib-test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) ptlib-test
