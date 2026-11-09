# Neon OS

Neon OS is a dark, hacker-green x64 operating system prototype designed for experimentation and learning. The goal is to build a Linux-like environment with a Kali-inspired terminal, desktop customization tools, a curated app catalog, and built-in security tooling.

This repository is the starting point for a bootable x64 OS project, with:

- a minimal BIOS bootloader
- a bare-metal kernel skeleton
- a dark neon theme and terminal shell prototype
- a secure app catalog model with signed package metadata
- a malware checker / antivirus app concept

Status:
- Bootloader: implemented as a minimal x86 BIOS boot sector
- Kernel: basic text-mode kernel prototype for VGA output
- Terminal: command parser with themed system commands
- App Store: JSON-based curated catalog structure
- Security: malware scanner app stub with heuristic scoring

Build:

```bash
make
make run
```

Requirements:

- NASM
- qemu-system-x86_64
- a cross-compiler such as `x86_64-elf-gcc` (recommended for bare-metal builds)

Important note:

This is an educational prototype. A complete production-grade OS requires a real kernel, memory manager, scheduler, filesystem, device drivers, and a secure software packaging system.
