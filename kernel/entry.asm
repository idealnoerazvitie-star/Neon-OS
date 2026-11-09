global _start
extern kernel_main

section .text
bits 32

_start:
    cli
    call kernel_main
    hlt
    jmp $
