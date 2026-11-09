#include "neon.h"

static struct neon_user_app apps[8];
static uint8_t app_count = 0;

void userland_init(void) {
    app_count = 0;
    apps[app_count++] = (struct neon_user_app){1, "Theme Studio", "sha256:theme-studio-v1-signed", 1, 1};
    apps[app_count++] = (struct neon_user_app){2, "Terminal Boost", "sha256:terminal-boost-v1-signed", 1, 1};
    apps[app_count++] = (struct neon_user_app){3, "File Guardian", "sha256:file-guardian-v1-signed", 1, 1};
    print("Userland app registry initialized.\n");
}

void userland_list(void) {
    print("Trusted apps:\n");
    for (uint8_t i = 0; i < app_count; ++i) {
        print("  ");
        print(apps[i].name);
        print("\n");
    }
}
