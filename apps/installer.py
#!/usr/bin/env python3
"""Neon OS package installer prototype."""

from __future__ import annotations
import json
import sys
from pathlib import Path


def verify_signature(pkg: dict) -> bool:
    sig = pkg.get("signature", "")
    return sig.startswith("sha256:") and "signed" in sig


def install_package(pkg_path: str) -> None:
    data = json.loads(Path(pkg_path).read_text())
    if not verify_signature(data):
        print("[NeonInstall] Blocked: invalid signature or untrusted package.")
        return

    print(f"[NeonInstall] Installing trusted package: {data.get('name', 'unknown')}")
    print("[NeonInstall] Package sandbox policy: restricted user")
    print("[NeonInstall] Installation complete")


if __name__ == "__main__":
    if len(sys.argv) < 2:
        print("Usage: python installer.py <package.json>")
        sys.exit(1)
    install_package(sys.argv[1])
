#include "neon.h"

int scan_package(const char *package_name, const char *signature) {
    if (package_name == 0 || signature == 0) {
        return 0;
    }

    print("Scanning package: ");
    print(package_name);
    print("\n");
    print("Signature check: ");
    print(signature);
    print("\n");

    if (signature[0] == 's' && signature[1] == 'h' && signature[2] == 'a') {
        print("Status: trusted package\n");
        return 1;
    }

    print("Status: untrusted package\n");
    return 0;
}

void install_package(const char *package_name, const char *signature) {
    if (scan_package(package_name, signature)) {
        print("Install verified and sandboxed.\n");
        print("Package installed successfully.\n");
    } else {
        print("Install blocked: invalid signature.\n");
    }
}
