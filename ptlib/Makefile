INC=-I./include/
OPTS=-O3
TARGET = libptlib.a
CXX=gcc

$(TARGET): ptl_image.o ptl_scene.o ptl_traceable_list.o ptl_util.o 
	ar rcs bin/$(TARGET) build/ptl_image.o build/ptl_scene.o build/ptl_traceable_list.o build/ptl_util.o 

ptl_image.o:
	$(CXX) $(OPTS) $(INC) -c src/ptl_image.c -o build/ptl_image.o 

ptl_traceable_list.o: 
	$(CXX) $(OPTS) $(INC) -c src/ptl_traceable_list.c -o build/ptl_traceable_list.o 

ptl_scene.o: ptl_image.o  ptl_traceable_list.o 
	$(CXX) $(OPTS) $(INC) -c src/ptl_scene.c -o build/ptl_scene.o 

ptl_util.o: 
	$(CXX) $(OPTS) $(INC) -c src/ptl_util.c -o build/ptl_util.o 

libs: libptlib.a 

clean:
	rm -rf build/*
	rm -rf bin/*
