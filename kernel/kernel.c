#include "neon.h"

static volatile uint16_t *const VGA_MEMORY = (volatile uint16_t *)VGA_ADDRESS;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static int str_equals(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0' && *a == *b) {
        ++a;
        ++b;
    }
    return *a == *b;
}

static int starts_with(const char *text, const char *prefix) {
    while (*prefix != '\0') {
        if (*text != *prefix) {
            return 0;
        }
        ++text;
        ++prefix;
    }
    return 1;
}

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

void print_hex32(uint32_t value) {
    const char *digits = "0123456789ABCDEF";
    char buffer[9];
    for (int i = 7; i >= 0; --i) {
        buffer[i] = digits[value & 0xF];
        value >>= 4;
    }
    buffer[8] = '\0';
    print(buffer);
}

static void cmd_help(void) {
    print("Neon OS Shell\n");
    print("help       Show commands\n");
    print("whoami     Show identity\n");
    print("ls         List files\n");
    print("sysinfo    Show system info\n");
    print("theme      Show theme profile\n");
    print("apps       Show app catalog\n");
    print("scan       Run malware scan\n");
    print("install    Install a signed package\n");
    print("memory     Show memory state\n");
    print("process    Show process list\n");
    print("desktop    Show desktop widgets\n");
    print("clear      Clear screen\n");
    print("reboot     Restart OS\n");
}

static void cmd_whoami(void) {
    print("User: root\n");
    print("Role: Neon administrator\n");
    print("Shell: neon-shell v0.6\n");
}

static void cmd_ls(void) {
    print("/root\n");
    print("  neon-system\n");
    print("  apps\n");
    print("  config\n");
    print("  downloads\n");
    print("  themes\n");
    fs_list();
}

static void cmd_sysinfo(void) {
    print("Neon OS v0.6\n");
    print("Architecture: x86 protected-mode prototype\n");
    print("Kernel: freestanding C + VGA shell\n");
    print("Theme: Dark Black + Neon Green\n");
    print("Security: signed app checks\n");
    print("Process manager: active\n");
}

static void cmd_theme(void) {
    print("Theme profile: Neon Black\n");
    print("Accent: #39FF14\n");
    print("Background: #050B08\n");
    print("Terminal glow: active\n");
}

static void cmd_apps(void) {
    print("Neon Market\n");
    print("trusted packages:\n");
    print("  Theme Studio\n");
    print("  Terminal Boost\n");
    print("  File Guardian\n");
    print("  Neon Antivirus\n");
    print("  Desktop Widgets\n");
}

static void cmd_scan(void) {
    print("Malware signature scan\n");
    print("Status: clean\n");
    print("Detected markers: 0\n");
    print("Heuristic score: 6/100\n");
}

static void cmd_install(void) {
    install_package("Neon Antivirus", "sha256:neon-antivirus-v1-signed");
}

static void cmd_memory(void) {
    memory_dump();
}

static void cmd_process(void) {
    process_list();
}

static void cmd_desktop(void) {
    desktop_init();
    widget_list();
}

static void cmd_clear(void) {
    clear_screen();
    print("Neon OS shell initialized.\n");
}

static void cmd_reboot(void) {
    print("Rebooting Neon OS...\n");
    __asm__ volatile ("cli; hlt");
}

void dispatch_command(const char *command) {
    if (command[0] == '\0') {
        return;
    }

    if (str_equals(command, "help") || starts_with(command, "help ")) {
        cmd_help();
        return;
    }
    if (str_equals(command, "whoami")) {
        cmd_whoami();
        return;
    }
    if (str_equals(command, "ls")) {
        cmd_ls();
        return;
    }
    if (str_equals(command, "sysinfo")) {
        cmd_sysinfo();
        return;
    }
    if (str_equals(command, "theme")) {
        cmd_theme();
        return;
    }
    if (str_equals(command, "apps")) {
        cmd_apps();
        return;
    }
    if (str_equals(command, "scan")) {
        cmd_scan();
        return;
    }
    if (str_equals(command, "install")) {
        cmd_install();
        return;
    }
    if (str_equals(command, "memory")) {
        cmd_memory();
        return;
    }
    if (str_equals(command, "process")) {
        cmd_process();
        return;
    }
    if (str_equals(command, "desktop")) {
        cmd_desktop();
        return;
    }
    if (str_equals(command, "clear")) {
        cmd_clear();
        return;
    }
    if (str_equals(command, "reboot")) {
        cmd_reboot();
        return;
    }

    print("Unknown command. Try 'help'.\n");
}

static void demo_banner(void) {
    print("Neon OS v0.6\n");
    print("Dark mode active\n");
    print("Kali-inspired shell ready\n");
    print("Store security: verified packages only\n");
    print("Malware scanning: enabled\n");
    print("Desktop widgets: active\n");
    print("\n");
}

void kernel_main(void) {
    clear_screen();
    memory_init();
    fs_init();
    idt_init();
    pic_init();
    keyboard_init();
    process_init();
    desktop_init();
    demo_banner();
    dispatch_command("help");
    print("\n");
    dispatch_command("sysinfo");
    print("\n");
    dispatch_command("apps");
    print("\n");
    dispatch_command("scan");
    print("\n");
    dispatch_command("install");
    print("\n");

    shell_run();
}
