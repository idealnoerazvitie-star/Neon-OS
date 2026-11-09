# Neon OS Architecture

## 1. Boot sequence
The bootloader is responsible for loading the kernel and switching the CPU into protected mode. This is the entry point for the OS and serves as the main gatekeeper before the kernel takes over.

## 2. Kernel services
The kernel is structured into a few major subsystems:
- VGA text-mode console
- memory layer
- filesystem registry
- keyboard handling
- IDT/PIC control
- package verification and app install manager

## 3. Security model
Every app in Neon Market is treated as a package. Packages must pass verification and are then run in a restricted sandbox profile. The design follows a "trusted source + signature check + quarantine" flow.

## 4. Future expansion
The next milestones are:
- userland ELF loading
- real filesystem driver
- task scheduler
- desktop UI and theme manager
- package repository and signed manifest system
- malware intelligence and behavior scanning
