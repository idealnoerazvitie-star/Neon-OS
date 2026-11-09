#include "neon.h"

static struct neon_process process_table[8];
static uint32_t process_count = 0;

void process_init(void) {
    process_count = 0;
    process_table[process_count++] = (struct neon_process){1, "neon-kernel", 255, 1};
    process_table[process_count++] = (struct neon_process){2, "neon-shell", 200, 1};
    process_table[process_count++] = (struct neon_process){3, "theme-studio", 150, 1};
    process_table[process_count++] = (struct neon_process){4, "neon-antivirus", 180, 1};
    print("Process table initialized.\n");
}

void process_list(void) {
    print("Running processes:\n");
    for (uint32_t i = 0; i < process_count; ++i) {
        print("  PID=");
        print_hex32(process_table[i].pid);
        print(" NAME=");
        print(process_table[i].name);
        print(" PRIORITY=");
        print_hex32(process_table[i].priority);
        print("\n");
    }
}
