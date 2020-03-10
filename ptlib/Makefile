CC = gcc  # C compiler
CFLAGS = -fPIC -Wall -Wextra -I./include/
LDFLAGS = -shared 
RM = rm -f
TARGET_LIB = libpt.so
TARGET_PATH = /usr/local/lib/${TARGET_LIB}

SRCS = src/ptl_image.c src/ptl_material.c src/ptl_ray.c src/ptl_scene.c src/ptl_sphere.c src/ptl_traceable_list.c src/ptl_traceable.c src/ptl_util.c src/ptl_vector.c src/ptl_rng.c src/ptl_list.c src/ptl_radiance.c src/ptl_render_cpu.c src/ptl_render_gpu.c
OBJS = $(SRCS:.c=.o)

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g -DDEBUG
else
	CFLAGS += -O3 -fdisable-tree-cunrolli -march=native
endif

OPENMP ?= 1
ifeq ($(OPENMP), 1)
	CFLAGS += -fopenmp
else
	CFLAGS += -DMAKE_OPENMP_OVERRIDE
endif

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