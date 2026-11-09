#include "neon.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t value = 0;
    __asm__ volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}

char keyboard_read(void) {
    while ((inb(0x64) & 0x01) == 0) {
    }

    uint8_t scan = inb(0x60);
    if (scan & 0x80) {
        return 0;
    }

    if (scan == 0x1C) {
        return '\n';
    }

    if (scan == 0x0E) {
        return '\b';
    }

    static const char keys[] = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./";
    if (scan >= 0x02 && scan <= 0x3A) {
        return keys[scan - 0x02];
    }

    return 0;
}
