NASM = nasm
QEMU = qemu-system-x86_64
CC = x86_64-elf-gcc
LD = x86_64-elf-ld

CFLAGS = -ffreestanding -fno-pie -fno-stack-protector -m32 -Wall -Wextra -O2 -nostdlib -nodefaultlibs -nostartfiles
LDFLAGS = -Ttext 0x1000 --oformat binary -e _start

all: build/neon.img

build:
	mkdir -p build

boot/boot.bin: boot/boot.asm
	$(NASM) -f bin -o $@ $<

kernel/kernel.bin: kernel/kernel.c | build
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

build/neon.img: boot/boot.bin kernel/kernel.bin | build
	cp boot/boot.bin build/neon.img
	dd if=kernel/kernel.bin of=build/neon.img bs=512 seek=1 conv=notrunc

run: build/neon.img
	$(QEMU) -drive file=build/neon.img,format=raw

clean:
	rm -rf build

.PHONY: all run clean
