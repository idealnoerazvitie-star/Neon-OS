# Neon OS Milestone Roadmap

## Phase 1 — Bootloader and kernel entry
- BIOS boot sector
- sector loading into memory
- switch to protected mode
- jump into C kernel

## Phase 2 — Console and shell
- VGA text mode
- neon green on black theme
- command parser
- help, info, apps, scan, install, reboot commands

## Phase 3 — Keyboard and input loop
- PS/2 keyboard drivers
- command input buffer
- backspace and newline handling
- shell prompt

## Phase 4 — Memory management
- memory map layout
- region tracking
- allocator skeleton
- heap and page tracking

## Phase 5 — Filesystem and app metadata
- file registry model
- package manifest format
- trusted flags and permissions
- base directory structure

## Phase 6 — Userland and process framework
- process table
- PIDs and priorities
- app lifecycle model
- ELF loading design

## Phase 7 — App Market
- curated catalog
- trusted package list
- signature validation
- sandbox policy
- install system

## Phase 8 — Malware and antivirus
- heuristics
- suspicious markers
- quarantine behavior
- security logs

## Phase 9 — Desktop and customization
- widgets
- system tray style taskbar
- theme presets
- profile switching

## Phase 10 — Hardening and release prep
- verified boot principles
- secure package enforcement
- memory protections
- audit policies

## Phase 11 — Production-grade OS work
- paging
- scheduling
- drivers
- userspace runtime
- stability testing
