#include "neon.h"

typedef struct {
    uint16_t base_low;
    uint16_t base_high;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t offset_low;
    uint16_t offset_high;
} __attribute__((packed)) interrupt_gate_t;

static interrupt_gate_t idt[256];

void idt_init(void) {
    for (int i = 0; i < 256; ++i) {
        idt[i].base_low = 0x0000;
        idt[i].base_high = 0x0000;
        idt[i].selector = 0x08;
        idt[i].always0 = 0;
        idt[i].flags = 0x8E;
        idt[i].offset_low = 0x0000;
        idt[i].offset_high = 0x0000;
    }

    print("IDT initialized.\n");
}

void pic_init(void) {
    print("PIC initialized.\n");
}
