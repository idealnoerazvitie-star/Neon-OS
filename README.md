# Neon OS

Neon OS is a dark, hacker-green operating system prototype for x86/x64 learning and experimentation.

It is intentionally designed to feel like a Kali-style terminal with a modern app ecosystem and a security-first mindset, while remaining a practical, modular project that can be built in phases.

Project goals:
- bootable kernel prototype
- dark neon UI theme
- terminal commands inspired by Linux and Kali
- app-store model for trusted software
- malware checker and quarantine workflows
- userland app support and desktop widgets
- production-grade design notes for future hardening

Status:
- Bootloader prototype exists
- Protected-mode bootstrap structure exists
- Kernel console and shell prototype exists
- App catalog and security docs exist
- This project remains an educational bare-metal OS foundation, not a complete production-ready OS

Build plan:
1. Bootloader and protected-mode entry
2. VGA console and shell
3. Keyboard input
4. Memory manager
5. Filesystem and package metadata
6. Userspace and process system
7. Trusted app catalog
8. Malware scanner and quarantine model
9. Desktop theming and widgets
10. Hardening and release prep

Build:

```bash
make
make run
```

Requirements:
- NASM
- GNU Make
- binutils
- QEMU (`qemu-system-i386`)
- optionally `i686-elf-gcc` or equivalent

Note:
This repository is a serious prototype scaffold. A true complete OS requires paging, scheduling, drivers, ELF userland, filesystem engineering, secure package signing, and desktop infrastructure.
