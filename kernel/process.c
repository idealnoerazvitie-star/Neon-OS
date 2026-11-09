#include "neon.h"

static struct neon_process processes[8];
static uint8_t proc_count = 0;

void process_init(void) {
    proc_count = 0;
    processes[proc_count++] = (struct neon_process){1, "neon-kernel", 255, 1};
    processes[proc_count++] = (struct neon_process){2, "neon-shell", 200, 1};
    processes[proc_count++] = (struct neon_process){3, "theme-studio", 150, 1};
    print("Process table initialized.\n");
}

void process_list(void) {
    print("Running processes:\n");
    for (uint8_t i = 0; i < proc_count; ++i) {
        print("  ");
        print(processes[i].name);
        print("\n");
    }
}
