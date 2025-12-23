BUILD_DIR := build

CC := gcc
CCFLAGS := -Ofast -m32 -Wno-pointer-to-int-cast -I../include
MAKE := make

SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)/%,$(SOURCES))
OUTPUT=$(patsubst src/%.c,%,$(SOURCES))
LIBRARY := ../linked.o

default: mkdir build

mkdir:
	mkdir -p ${BUILD_DIR}

$(BUILD_DIR)/%: src/%.c
	$(CC) $(CCFLAGS) $^ -o $@ $(LIBRARY)

build: $(OBJECTS)
	cp $(OBJECTS) ./

run_tests: $(OUTPUT)
	@for TEST in $^; do \
		echo -n "Testing $${TEST}: "; \
		./$$TEST 2>/dev/null 1>/dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "PASSED"; \
		else \
			echo "FAILED"; \
		fi; \
	done

clean:
	rm -rf ${BUILD_DIR} ${OUTPUT}
