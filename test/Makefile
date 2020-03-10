CC = gcc
CFLAGS = -I../ptlib/include -fopenmp -Wall
LDFLAGS = -lpt -lm
DEPS = 
OBJ = ptlib-test.o bitmap.o

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g -DDEBUG
else
	CFLAGS += -O3
endif

all: ptlib-test

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ptlib-test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) ptlib-test
