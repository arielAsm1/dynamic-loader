CC := gcc

CFLAGS := -ffreestanding -fno-builtin -nostdlib -fPIC -fno-stack-protector -mno-red-zone
LDFLAGS := -L. -lmylib

SRC_LIB := mylib.c
LIB := libmylib.so

SRC_PROG := testprog.c
PROG := testprog

all: $(LIB) $(PROG)

$(LIB): $(SRC_LIB)
	$(CC) $(CFLAGS) -shared $< -o $@

$(PROG): $(SRC_PROG) $(LIB)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f $(LIB) $(PROG)
