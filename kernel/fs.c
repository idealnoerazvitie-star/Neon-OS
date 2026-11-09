#include "neon.h"

static struct neon_file file_table[16];
static uint8_t file_count = 0;

void fs_init(void) {
    file_count = 0;
    fs_register("theme-studio", 2048, 1);
    fs_register("terminal-boost", 4096, 1);
    fs_register("file-guardian", 8192, 1);
    fs_register("neon-antivirus", 16384, 1);
    print("Filesystem registry initialized.\n");
}

void fs_register(const char *name, uint32_t size, uint8_t trusted) {
    if (file_count >= 16) {
        return;
    }

    struct neon_file *entry = &file_table[file_count++];
    for (int i = 0; i < 15; ++i) {
        entry->name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
    entry->name[15] = '\0';
    entry->size = size;
    entry->trusted = trusted;
    entry->flags = trusted ? 0x01 : 0x00;
}

void fs_list(void) {
    for (uint8_t i = 0; i < file_count; ++i) {
        print("  ");
        print(file_table[i].name);
        print("  size=");
        print_hex32(file_table[i].size);
        print("\n");
    }
}
