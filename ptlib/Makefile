INC=-I./include/
OPTS=-O3
TARGET = libptlib.a
CXX=gcc

$(TARGET): ptl_image.o ptl_scene.o ptl_traceable_list.o ptl_util.o ptl_vector.o ptl_material.o ptl_ray.o ptl_traceable.o
	ar rcs bin/$(TARGET) build/ptl_image.o build/ptl_scene.o build/ptl_traceable_list.o build/ptl_util.o build/ptl_vector.o build/ptl_material.o build/ptl_ray.o build/ptl_traceable.o

ptl_image.o:
	$(CXX) $(OPTS) $(INC) -c src/ptl_image.c -o build/ptl_image.o 

ptl_traceable_list.o: 
	$(CXX) $(OPTS) $(INC) -c src/ptl_traceable_list.c -o build/ptl_traceable_list.o 

ptl_scene.o: ptl_image.o  ptl_traceable_list.o 
	$(CXX) $(OPTS) $(INC) -c src/ptl_scene.c -o build/ptl_scene.o 

ptl_util.o: 
	$(CXX) $(OPTS) $(INC) -c src/ptl_util.c -o build/ptl_util.o 

ptl_vector.o:
	$(CXX) $(OPTS) $(INC) -c src/ptl_vector.c -o build/ptl_vector.o 

ptl_material.o:
	$(CXX) $(OPTS) $(INC) -c src/ptl_material.c -o build/ptl_material.o 

ptl_ray.o: 
	$(CXX) $(OPTS) $(INC) -c src/ptl_ray.c -o build/ptl_ray.o 

ptl_traceable.o:
	$(CXX) $(OPTS) $(INC) -c src/ptl_traceable.c -o build/ptl_traceable.o 

libs: libptlib.a 

clean:
	rm -rf build/*
	rm -rf bin/*
