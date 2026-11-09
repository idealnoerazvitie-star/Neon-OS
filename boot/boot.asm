[BITS 16]
[ORG 0x7C00]

KERNEL_OFFSET equ 0x1000

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, boot_msg
    call print_string

    mov dl, 0x80
    mov bx, KERNEL_OFFSET
    mov dh, 20
    mov cl, 2
    call disk_load

    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEG:init_pm

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

disk_load:
    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13
    jc disk_error
    ret

disk_error:
    mov si, disk_err
    call print_string
    cli
    hlt

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp KERNEL_OFFSET

GDT:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF

gdt_descriptor:
    dw 23
    dd GDT

CODE_SEG equ 0x08
DATA_SEG equ 0x10

boot_msg db "Neon OS booting...", 13, 10, 0
disk_err db "Disk read error.", 13, 10, 0

TIMES 510 - ($ - $$) db 0
DW 0xAA55
