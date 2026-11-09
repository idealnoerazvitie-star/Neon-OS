# Neon OS

Neon OS is a dark, hacker-green operating system prototype built as a practical learning project for x86 architecture and bare-metal kernel development. It is designed with a Kali-inspired terminal feel, a curated application catalog, and security-first software concepts.

This repository now includes:
- BIOS bootloader and protected-mode startup sequence
- VGA text-mode kernel with dark neon styling
- keyboard driver foundation for user interaction
- memory and filesystem layer prototypes
- real process and desktop scaffolding for future userland integration
- app market / installer model for signed-free software
- malware detection and security documentation
- architecture and hardening docs for future expansion

Project vision:
- x86 protected-mode kernel skeleton
- command-line shell with Linux-inspired commands
- app store with signature verification and sandboxing
- malware scanning and quarantine heuristics
- desktop customization engine and widget support
- future real userland and package manager integration

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
- optionally `i686-elf-gcc` or a compatible cross-compiler

Notes:
- This is still a prototype OS, not a production-grade Linux distribution.
- A complete system would require paging, preemptive scheduling, real drivers, ELF userspace, secure package signing, and a robust desktop manager.
- The goal of this repository is to create a serious foundation for those features in a manageable and testable form.
