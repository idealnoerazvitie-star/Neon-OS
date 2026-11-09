#include "neon.h"

static struct neon_widget widgets[4] = {
    {1, "Clock", 1},
    {2, "System", 1},
    {3, "Theme", 1},
    {4, "Security", 1}
};

void desktop_init(void) {
    print("Desktop environment initialized.\n");
    print("Wallpaper: Neon Black\n");
    print("Taskbar: enabled\n");
}

void widget_list(void) {
    print("Desktop widgets:\n");
    for (int i = 0; i < 4; ++i) {
        print("  ");
        print(widgets[i].label);
        print(" [visible: ");
        print(widgets[i].visible ? "yes" : "no");
        print("]\n");
    }
}
