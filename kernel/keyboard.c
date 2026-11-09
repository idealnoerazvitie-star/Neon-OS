#include "neon.h"

static uint8_t keyboard_ready = 0;

static inline uint8_t inb(uint16_t port) {
    uint8_t value = 0;
    __asm__ volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

void keyboard_init(void) {
    keyboard_ready = 1;
    outb(0x21, 0xFD);
    print("Keyboard driver initialized.\n");
}

char keyboard_read(void) {
    if (!keyboard_ready) {
        return 0;
    }

    while ((inb(0x64) & 0x01) == 0) {
    }

    uint8_t scan = inb(0x60);
    if (scan & 0x80) {
        return 0;
    }

    static const char rows[] = "1234567890-=
qwertyuiop[]\nasdfghjkl;'\nzxcvbnm,./";
    if (scan >= 0x02 && scan <= 0x3A) {
        return rows[scan - 0x02];
    }

    return 0;
}
