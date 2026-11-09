# Neon OS Linux-like Distro Foundation

This document describes the distro structure added to the repo so Neon OS looks and behaves more like a normal Linux-based operating system in its project layout.

## Target layout

The project now includes a minimal Linux-like directory structure:

- `/etc` for system config, identity, services, and user metadata
- `/usr/bin` for user-mode commands
- `/usr/share/applications` for app launchers
- `/var/lib/neon` for package registry and runtime metadata
- `/home/neon` for a default user profile

## Included system features

- OS metadata via `os-release`
- host identity and issue banner
- users and groups
- shell listing
- package registry with application metadata
- desktop entries for installed tools
- command shims for common Linux-style utilities

## Notes

This does not attempt to transform the bare-metal prototype into a complete GNU/Linux distribution. It creates the standard project structure and system conventions expected from a Linux-esque environment while preserving the current kernel-first design.
