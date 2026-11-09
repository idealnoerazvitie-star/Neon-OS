#ifndef NEON_H
#define NEON_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000
#define GREEN 0x0A
#define WHITE 0x0F

void clear_screen(void);
void put_char(char ch);
void print(const char *text);
char keyboard_read(void);
void shell_run(void);
void shell_print_prompt(void);

#endif
