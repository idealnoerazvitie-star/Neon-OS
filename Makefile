ASM ?= nasm
CC ?= i686-elf-gcc
LD ?= i686-elf-ld
OBJCOPY ?= objcopy
QEMU ?= qemu-system-i386

ifeq ($(shell command -v $(CC) >/dev/null 2>&1; echo $$?), 1)
CC = gcc
endif

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -fno-builtin -O2 -Wall -Wextra -Iinclude
LDFLAGS = -m elf_i386 -nostdlib -nodefaultlibs -static

BUILD_DIR = build
BOOT_BIN = $(BUILD_DIR)/boot.bin
KERNEL_ELF = $(BUILD_DIR)/neon.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
IMAGE = $(BUILD_DIR)/neon.img

.PHONY: all run clean

all: $(IMAGE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BOOT_BIN): boot/boot.asm | $(BUILD_DIR)
	$(ASM) -f bin -o $@ $<

$(BUILD_DIR)/entry.o: kernel/entry.asm | $(BUILD_DIR)
	$(ASM) -f elf32 -o $@ $<

$(BUILD_DIR)/kernel.o: kernel/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/memory.o: kernel/memory.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/fs.o: kernel/fs.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/interrupts.o: kernel/interrupts.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/keyboard.o: kernel/keyboard.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/shell.o: kernel/shell.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/process.o: kernel/process.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/desktop.o: kernel/desktop.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/userland.o: kernel/userland.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(KERNEL_ELF): $(BUILD_DIR)/entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/fs.o $(BUILD_DIR)/interrupts.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/shell.o $(BUILD_DIR)/process.o $(BUILD_DIR)/desktop.o $(BUILD_DIR)/userland.o linker.ld
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $(BUILD_DIR)/entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/fs.o $(BUILD_DIR)/interrupts.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/shell.o $(BUILD_DIR)/process.o $(BUILD_DIR)/desktop.o $(BUILD_DIR)/userland.o
	$(OBJCOPY) -O binary $@ $(KERNEL_BIN)

$(IMAGE): $(BOOT_BIN) $(KERNEL_ELF)
	dd if=/dev/zero of=$@ bs=512 count=2880 status=none
	dd if=$(BOOT_BIN) of=$@ bs=512 count=1 conv=notrunc status=none
	dd if=$(KERNEL_BIN) of=$@ bs=512 seek=1 conv=notrunc status=none

run: $(IMAGE)
	$(QEMU) -drive file=$(IMAGE),format=raw -display none

clean:
	rm -rf $(BUILD_DIR)
