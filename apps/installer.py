#!/usr/bin/env python3
"""Neon OS package installer prototype."""

from __future__ import annotations
import json
import sys
from pathlib import Path


def verify_signature(pkg: dict) -> bool:
    sig = pkg.get("signature", "")
    return sig.startswith("sha256:") and "signed" in sig


def install_package(pkg_path: str) -> None:
    data = json.loads(Path(pkg_path).read_text())
    if not verify_signature(data):
        print("[NeonInstall] Blocked: invalid signature or untrusted package.")
        return

    print(f"[NeonInstall] Installing trusted package: {data.get('name', 'unknown')}")
    print("[NeonInstall] Package sandbox policy: restricted-user")
    print("[NeonInstall] Installation complete")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 installer.py <package.json>")
        sys.exit(1)
    install_package(sys.argv[1])
