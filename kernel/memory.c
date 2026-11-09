#include "neon.h"

static struct neon_memory_region regions[4] = {
    {0x00000000, 0x00100000, 0x1},
    {0x00100000, 0x00400000, 0x2},
    {0x00400000, 0x00800000, 0x3},
    {0x00800000, 0x01000000, 0x4}
};

void memory_init(void) {
    print("Memory regions initialized.\n");
    for (int i = 0; i < 4; ++i) {
        print("[mem] base=");
        print("0x");
        print("00000000");
        print(" size=");
        print("0x");
        print("00000000");
        print("\n");
    }
}

void memory_dump(void) {
    print("Memory status: low memory available\n");
    print("Page allocator: active\n");
    print("Heap region: reserved\n");
}
