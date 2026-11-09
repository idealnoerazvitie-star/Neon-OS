#ifndef NEON_H
#define NEON_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000
#define GREEN 0x0A
#define WHITE 0x0F

struct neon_memory_region {
    uint32_t base;
    uint32_t size;
    uint32_t type;
};

struct neon_file {
    char name[16];
    uint32_t size;
    uint32_t flags;
    uint8_t trusted;
};

struct neon_process {
    uint32_t pid;
    char name[16];
    uint32_t priority;
    uint8_t running;
};

struct neon_user_app {
    uint32_t id;
    char name[16];
    char signature[32];
    uint8_t trusted;
    uint8_t sandboxed;
};

void clear_screen(void);
void put_char(char ch);
void print(const char *text);
char keyboard_read(void);
void shell_run(void);
void shell_print_prompt(void);
void memory_init(void);
void memory_dump(void);
void fs_init(void);
void fs_register(const char *name, uint32_t size, uint8_t trusted);
void fs_list(void);
void process_init(void);
void process_list(void);
void userland_init(void);
void userland_list(void);
void install_package(const char *name, const char *signature);
void malware_scan(void);
void desktop_init(void);
void widget_list(void);

#endif
