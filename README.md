# Neon OS

Neon OS is currently a kernel-first operating system prototype with a bare-metal x86 boot flow and a terminal shell. This branch adds a Linux-like distro foundation layer so the project has the structure and conventions expected from a normal distro: system files, user accounts, directory layout, base commands, app metadata, and package registry.

## Filesystem layout

The repository now includes a minimal Linux-style scaffolding:

- `etc/` for system configuration and distro metadata
- `usr/bin/` for base user commands
- `usr/share/applications/` for desktop launchers
- `var/lib/neon/` for package and system metadata
- `home/neon/` for a default user profile

## Included foundations

- `/etc/os-release` for distro identity
- `/etc/passwd` and `/etc/group` for users/groups
- `/etc/shells` listing supported shells
- `/usr/bin/neonctl` for system management
- `/usr/bin/neon-shell` for the local shell entrypoint
- `/usr/bin/ls`, `/usr/bin/cat`, `/usr/bin/ps` as Linux-like command shims
- desktop entries for base applications
- package metadata in `/var/lib/neon/packages.json`

This is intentionally a distro scaffold for the Neon OS project and not a full Ubuntu/Debian replacement. It gives the repo a realistic Linux-like structure while preserving the kernel prototype architecture.

## Build and usage

This branch is a filesystem and metadata foundation; it does not replace the kernel boot flow.

```bash
make
make run
```
