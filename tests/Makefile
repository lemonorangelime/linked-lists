BUILD_DIR := build

CC := gcc
CCFLAGS := -O2 -m32 -Wno-pointer-to-int-cast -I../include
MAKE := make

SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)/%,$(SOURCES))

LIBRARY := ../linked.o

default: mkdir build

mkdir:
	mkdir -p ${BUILD_DIR}

$(BUILD_DIR)/%: src/%.c
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBRARY)

build: $(OBJECTS)
	echo here

clean:
	rm -rf ${BUILD_DIR}
