#include "neon.h"

static char shell_buffer[128];
static uint32_t shell_index = 0;

static void shell_print_prompt(void) {
    print("neon@neon-os:~$ ");
}

static void shell_execute_buffer(void) {
    if (shell_index == 0) {
        shell_print_prompt();
        return;
    }

    shell_buffer[shell_index] = '\0';
    dispatch_command(shell_buffer);
    print("\n");
    shell_index = 0;
    shell_print_prompt();
}

void shell_run(void) {
    shell_print_prompt();

    while (1) {
        char ch = keyboard_read();
        if (ch == 0) {
            __asm__ volatile ("hlt");
            continue;
        }

        if (ch == '\b') {
            if (shell_index > 0) {
                shell_index--;
                print("\b ");
            }
            continue;
        }

        if (ch == '\n') {
            shell_execute_buffer();
            continue;
        }

        if (shell_index < sizeof(shell_buffer) - 1) {
            shell_buffer[shell_index++] = ch;
            put_char(ch);
        }
    }
}
