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

static void cmd_help(void) {
    print("Neon OS shell\n");
    print("help        Show commands\n");
    print("clear       Clear screen\n");
    print("sysinfo     Show system info\n");
    print("theme       Show theme\n");
    print("memory      Memory status\n");
    print("process     Process status\n");
    print("apps        Show apps\n");
    print("reboot      Restart system\n");
}

static void cmd_sysinfo(void) {
    print("Neon OS v0.3\n");
    print("Kernel: boot, shell, memory, userspace foundations\n");
    print("Theme: Dark Black / Neon Green\n");
}

static void cmd_theme(void) {
    print("Theme profile: Neon Black\n");
    print("Accent: #39FF14\n");
}

static void cmd_clear(void) {
    clear_screen();
    print("Neon OS shell initialized.\n");
}

static void cmd_memory(void) {
    memory_dump();
}

static void cmd_process(void) {
    process_list();
}

static void cmd_apps(void) {
    userland_list();
}

static void cmd_reboot(void) {
    print("Rebooting Neon OS...\n");
    __asm__ volatile ("cli; hlt");
}

static int str_equals(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0' && *a == *b) {
        ++a;
        ++b;
    }
    return *a == *b;
}

static void dispatch_command(const char *cmd) {
    if (str_equals(cmd, "help")) {
        cmd_help();
        return;
    }
    if (str_equals(cmd, "sysinfo")) {
        cmd_sysinfo();
        return;
    }
    if (str_equals(cmd, "theme")) {
        cmd_theme();
        return;
    }
    if (str_equals(cmd, "clear")) {
        cmd_clear();
        return;
    }
    if (str_equals(cmd, "memory")) {
        cmd_memory();
        return;
    }
    if (str_equals(cmd, "process")) {
        cmd_process();
        return;
    }
    if (str_equals(cmd, "apps")) {
        cmd_apps();
        return;
    }
    if (str_equals(cmd, "reboot")) {
        cmd_reboot();
        return;
    }

    print("Unknown command. Try 'help'.\n");
}

void shell_print_prompt(void) {
    print("neon@neon-os:~$ ");
}

void shell_run(void) {
    char buffer[64];
    uint32_t index = 0;

    shell_print_prompt();

    while (1) {
        char ch = keyboard_read();
        if (ch == 0) {
            __asm__ volatile ("hlt");
            continue;
        }

        if (ch == '\b') {
            if (index > 0) {
                index--;
                print("\b ");
            }
            continue;
        }

        if (ch == '\n') {
            buffer[index] = '\0';
            dispatch_command(buffer);
            print("\n");
            index = 0;
            shell_print_prompt();
            continue;
        }

        if (index < 63) {
            buffer[index++] = ch;
            put_char(ch);
        }
    }
}

void kernel_main(void) {
    clear_screen();
    memory_init();
    fs_init();
    process_init();
    userland_init();
    print("Neon OS\n");
    print("Phase 3: memory, FS, and userspace foundations\n");
    print("Type 'help' to begin\n\n");
    shell_run();
}
