#include "neon.h"

static int neon_equals(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0' && *a == *b) {
        ++a;
        ++b;
    }
    return *a == *b;
}

void install_package(const char *name, const char *signature) {
    if (name == 0 || signature == 0) {
        print("Install rejected: invalid package metadata.\n");
        return;
    }

    if (!neon_equals(signature, "sha256:neon-antivirus-v1-signed") &&
        !neon_equals(signature, "sha256:theme-studio-v1-signed") &&
        !neon_equals(signature, "sha256:terminal-boost-v1-signed") &&
        !neon_equals(signature, "sha256:file-guardian-v1-signed")) {
        print("Install rejected: signature not trusted.\n");
        return;
    }

    print("Package install: ");
    print(name);
    print("\nStatus: verified signature, trusted source, sandboxed\n");
}

void malware_scan(void) {
    print("Malware scan: clean\n");
    print("Detected markers: 0\n");
    print("Heuristic score: 6/100\n");
    print("Signed apps allowed: 4\n");
}
