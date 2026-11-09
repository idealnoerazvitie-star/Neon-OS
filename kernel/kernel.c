#include "neon.h"

static volatile uint16_t *const VGA_MEMORY = (volatile uint16_t *)VGA_ADDRESS;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void clear_screen(void) {
    for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        VGA_MEMORY[i] = (uint16_t)(' ' | (GREEN << 8));
    }
    cursor_x = 0;
    cursor_y = 0;
}

void put_char(char ch) {
    if (ch == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (ch == '\r') {
        cursor_x = 0;
    } else {
        uint32_t index = (cursor_y * VGA_WIDTH) + cursor_x;
        VGA_MEMORY[index] = (uint16_t)(ch | (GREEN << 8));
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        for (uint32_t y = 1; y < VGA_HEIGHT; ++y) {
            for (uint32_t x = 0; x < VGA_WIDTH; ++x) {
                VGA_MEMORY[(y - 1) * VGA_WIDTH + x] = VGA_MEMORY[y * VGA_WIDTH + x];
            }
        }
        for (uint32_t x = 0; x < VGA_WIDTH; ++x) {
            VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (uint16_t)(' ' | (GREEN << 8));
        }
        cursor_y = VGA_HEIGHT - 1;
        cursor_x = 0;
    }
}

void print(const char *text) {
    while (*text != '\0') {
        put_char(*text++);
    }
}

static void print_banner(void) {
    print("Neon OS\n");
    print("Bootloader: online\n");
    print("Kernel: protected mode ready\n");
    print("Theme: Dark Black + Neon Green\n");
    print("Status: boot stage complete\n");
}

void kernel_main(void) {
    clear_screen();
    print_banner();

    while (1) {
        __asm__ volatile ("hlt");
    }
}
