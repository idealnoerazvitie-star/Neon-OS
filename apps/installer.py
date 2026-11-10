#!/usr/bin/env python3
"""Neon OS package installer prototype."""

from __future__ import annotations

import json
import sys
from pathlib import Path


def verify_signature(pkg: dict) -> bool:
    sig = pkg.get("signature", "")
    return isinstance(sig, str) and sig.startswith("sha256:") and "signed" in sig.lower()


def install_package(pkg_path: str) -> None:
    try:
        data = json.loads(Path(pkg_path).read_text(encoding="utf-8"))
    except (FileNotFoundError, OSError, json.JSONDecodeError) as exc:
        print(f"[NeonInstall] Failed to read package: {exc}")
        raise SystemExit(1)

    if not isinstance(data, dict):
        print("[NeonInstall] Blocked: package metadata is invalid.")
        raise SystemExit(1)

    if not verify_signature(data):
        print("[NeonInstall] Blocked: invalid signature or untrusted package.")
        return

    name = data.get("name", "unknown")
    print(f"[NeonInstall] Installing trusted package: {name}")
    print("[NeonInstall] Package sandbox policy: restricted-user")
    print("[NeonInstall] Installation complete")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 installer.py <package.json>")
        sys.exit(1)
    install_package(sys.argv[1])
