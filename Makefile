BUILD_DIR := build

CC := gcc
CCFLAGS := -O3 -fno-stack-protector -m32 -Wno-pointer-to-int-cast -Iinclude
ASM := nasm
ASMFLAGS := -f elf32
MAKE := make
AR := ar
LDFLAGS := -r -m32

SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

ASM_SOURCES=$(wildcard src/*.asm)
ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OUTPUT := linked.o

default: mkdir build

mkdir:
	mkdir -p ${BUILD_DIR}

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CCFLAGS) $^ -c -o $@

$(BUILD_DIR)/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

build: $(OBJECTS) $(ASM_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o ${OUTPUT}

clean:
	rm -rf ${BUILD_DIR} ${OUTPUT}
