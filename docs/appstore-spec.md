# Neon OS App Store Specification

## Goals
- Curate a free app catalog with trusted assets only
- Require package signatures before install
- Sandbox execution for untrusted or restricted packages
- Show clear installation status and scanner results

## Package fields
- name
- version
- category
- license
- signature
- sandbox
- description

## Verification flow
1. Package metadata is read from the catalog
2. The signature is checked for a valid trusted prefix
3. The package is sandboxed before execution
4. Malware scan runs before installation is allowed

## Security policy
Any package without a valid signature is rejected and quarantined.
