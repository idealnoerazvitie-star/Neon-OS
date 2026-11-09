# Neon OS App Store Specification

## Goals
- trusted-only package catalog
- free software distribution model
- signature verification before install
- sandboxing and quarantine for risky packages
- explicit security status in the UI

## Package schema
```json
{
  "name": "Theme Studio",
  "version": "1.0.0",
  "category": "Customization",
  "license": "Free",
  "signature": "sha256:theme-studio-v1-signed",
  "sandbox": "restricted-user",
  "description": "Customizes Neon OS themes and widgets."
}
```

## Verification flow
1. Read manifest
2. Validate signature format
3. Enforce trusted source allowlist
4. Scan for malware heuristics
5. Sandbox execution
6. Install only if all checks pass

## Safety rules
- Reject unsigned packages
- Quarantine suspicious packages
- Restrict write access to protected directories
- Display scan and install results clearly
