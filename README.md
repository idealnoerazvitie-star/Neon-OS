# Neon OS Phase 1: Bootloader + Protected Mode + VGA Kernel

This phase establishes the first real bootable kernel skeleton for Neon OS.

What is implemented:
- 16-bit BIOS boot sector
- reads kernel from disk
- enters protected mode
- jumps into a 32-bit C kernel
- prints a neon-green boot banner to VGA text mode

Files in this phase:
- boot/boot.asm
- kernel/entry.asm
- kernel/kernel.c
- linker.ld
- include/neon.h
- Makefile

Build and run:

```bash
make
make run
```

Requirements:
- NASM
- GNU Make
- binutils
- QEMU (`qemu-system-i386`)
- `i686-elf-gcc` or a compatible bare-metal cross-compiler

This is the first milestone of Neon OS and the foundation for all later phases.
