default: build_all

build_all: build_ptlib build_test

build_test: build_ptlib
	cd ./test && $(MAKE)

build_ptlib:
	cd ./ptlib && $(MAKE)

run: build_test
	cd ./test && ./ptlib-test

.PHONY: clean
clean:
	cd ./ptlib && $(MAKE) clean
	cd ./test && $(MAKE) clean



