# Neon OS

Neon OS is a dark, hacker-green x64 operating system prototype designed for experimentation, learning, and future real-world development. The project is intentionally inspired by the feeling of a Kali-like terminal and a modern app-store experience, while keeping the implementation practical and modular.

Features in this build:
- BIOS bootloader that loads a kernel into memory
- protected-mode startup architecture
- dark neon theme and terminal styling
- shell commands inspired by Kali and Linux tools
- app catalog with signed/free package metadata
- malware-scanning prototype and antivirus workflow
- roadmap for a more complete OS

What this version includes:
- boot/boot.asm: 16-bit bootloader that loads the kernel
- kernel/entry.asm: 32-bit protected-mode entry point
- kernel/kernel.c: console, terminal shell, commands, and demo system interface
- kernel/keyboard.c: PS/2 keyboard polling foundation
- apps/appstore.json: signed software catalog modeled after a curated app market
- docs/roadmap.md: development path toward a larger OS

Build and run:

```bash
make
make run
```

Requirements:
- NASM
- binutils
- GNU Make
- QEMU
- i686-elf-gcc or x86_64-elf-gcc with 32-bit support

Note:
This is a prototype operating system skeleton. It is not a full Linux distribution or a production-ready kernel. It is a serious foundation for learning how to build a bootable x64-style system with a dark hacker aesthetic and security-focused tooling.
