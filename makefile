CC := gcc
AS := nasm
LD := ld

CFLAGS := -ffreestanding -fno-builtin -nostdlib -Isrc/include -ggdb
ASFLAGS := -f elf64
LDFLAGS := -nostdlib -e _start

BUILD_DIR := build
BIN_DIR := bin
TARGET_NAME := loader

FINAL_TARGET := $(BIN_DIR)/$(TARGET_NAME)

SRC_C := $(wildcard src/*.c)
SRC_ASM := $(wildcard src/*.s)

OBJ_C := $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRC_C))
OBJ_ASM := $(patsubst src/%.s, $(BUILD_DIR)/%.o, $(SRC_ASM))
OBJ := $(OBJ_C) $(OBJ_ASM)

all: $(FINAL_TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(FINAL_TARGET): $(OBJ) | $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR)/%.o: src/%.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)