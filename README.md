# Neon OS

Neon OS is an **early bootable x86 prototype**, not yet a Linux distribution or a daily-use operating system. The current milestone is a BIOS boot sector that loads a small 32-bit kernel and displays a banner in VGA text mode. It does not yet have an interactive shell, keyboard input, a real filesystem, or the planned desktop/apps.

## Try it safely in QEMU

Run it in a virtual machine first; do not write the disk image to a physical drive.

### Requirements

- NASM
- GNU Make and binutils
- QEMU with `qemu-system-i386`
- `i686-elf-gcc` and `i686-elf-ld` (recommended bare-metal cross-compiler)

On Debian/Ubuntu, install the common tools with:

```bash
sudo apt update
sudo apt install make binutils nasm qemu-system-x86 gcc-multilib
```

If you use the distro's regular GCC instead of the recommended cross-compiler, build with `make CC=gcc LD=ld`.

### Build and boot

From the repository directory:

```bash
make
make run
```

`make` creates `build/neon.img`. `make run` opens QEMU with a visible display; close the QEMU window or press `Ctrl+C` in the launching terminal to stop it. To rebuild from scratch, run `make clean` and then `make`.

The bootloader currently loads only the first 16 kernel sectors (8192 bytes), and the build fails if the kernel exceeds that limit. This prototype targets legacy BIOS boot in QEMU; it is not UEFI-bootable and is not ready for real hardware.

## Current implementation

- 16-bit BIOS boot sector and disk read
- transition to 32-bit protected mode
- freestanding C kernel that writes a boot banner to VGA text memory

See `docs/roadmap.md` for planned work. The memory, process, filesystem, security, and app concepts described in the repository are scaffolding/plans, not complete operating-system services.
