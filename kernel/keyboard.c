#include "neon.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t value = 0;
    __asm__ volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}

char keyboard_read(void) {
    static uint8_t shift = 0;

    while ((inb(0x64) & 0x01) == 0) {
    }

    uint8_t scan = inb(0x60);
    uint8_t key = scan & 0x7F;

    if (scan == 0xE0) {
        return 0;
    }

    if (scan & 0x80) {
        if (key == 0x2A || key == 0x36) {
            shift = 0;
        }
        return 0;
    }

    if (key == 0x2A || key == 0x36) {
        shift = 1;
        return 0;
    }

    if (key == 0x1C) {
        return '\n';
    }

    if (key == 0x0E) {
        return '\b';
    }

    if (key == 0x39) {
        return ' ';
    }

    static const char lower[] = "1234567890-=qwertyuiop[]asdfghjkl;'`\\zxcvbnm,./ ";
    static const char upper[] = "!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"~|ZXCVBNM<>? ";

    if (key >= 0x02 && key <= 0x3A) {
        const char *map = shift ? upper : lower;
        return map[key - 0x02];
    }

    return 0;
}
