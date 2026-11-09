# Neon OS Architecture Overview

## Boot sequence
1. BIOS loads the boot sector
2. Bootloader reads the kernel image
3. CPU switches to protected mode
4. Kernel starts in C code
5. Console initializes and commands become available

## Core subsystems
- VGA console
- keyboard handler
- memory tracking
- filesystem / package registry
- process table
- app installation logic
- desktop widget layer

## Design philosophy
Neon OS follows a layered architecture:
- low-level boot and CPU setup
- kernel services
- userspace abstractions
- package validation
- desktop and customization

## Final ecosystem
The goal is a Linux-like development environment with a dark hacker aesthetic, a trusted app store, and security features that help users understand how real operating systems protect users and data.
