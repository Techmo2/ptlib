CC = gcc  # C compiler
CFLAGS = -fPIC -Wall -fopenmp -Wextra -O3 -g -I./include/
LDFLAGS = -shared 
RM = rm -f
TARGET_LIB = libpt.so
TARGET_PATH = /usr/local/lib/${TARGET_LIB}

SRCS = src/ptl_image.c src/ptl_material.c src/ptl_ray.c src/ptl_scene.c src/ptl_sphere.c src/ptl_traceable_list.c src/ptl_traceable.c src/ptl_util.c src/ptl_vector.c src/ptl_rng.c# source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)

.PHONY: install
install:
	mv -n ${TARGET_LIB} ${TARGET_PATH}
	ldconfig

.PHONY: uninstall
uninstall:
	${RM} ${TARGET_PATH}