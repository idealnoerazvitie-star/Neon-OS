# Neon OS Phase 3: Memory Manager + Filesystem + Userspace Foundations

This phase adds the next layers needed for a real OS:
- memory map region tracking
- basic filesystem registry
- userland app list
- process skeleton
- app store metadata

Features:
- memory_init()
- fs_init()
- fs_register()
- fs_list()
- userland_init()
- userland_list()
- process_init()
- process_list()

Build and run:

```bash
make
make run
```
