INC=-I../ptlib/include
LIB=../ptlib/bin/libptlib.a -lm
OPTS=-O3
CXX=gcc

TARGET=ptlib-test

$(TARGET):
	$(CXX) $(OPTS) $(INC) ptlib_test.c $(LIB) -o ptlib-test

clean:
	rm ptlib-test