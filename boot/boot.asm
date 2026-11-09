[BITS 16]
[ORG 0x7C00]

KERNEL_OFFSET equ 0x1000
BOOT_DRIVE db 0

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov [BOOT_DRIVE], dl

    mov si, neon_msg
    call print_string

    mov bx, KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov si, ready_msg
    call print_string

    jmp KERNEL_OFFSET

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
    mov si, disk_error_msg
    call print_string
    cli
    hlt

neon_msg db "Neon OS booting...", 0x0D, 0x0A, 0
ready_msg db "Kernel loaded and running.", 0x0D, 0x0A, 0
disk_error_msg db "Disk read error.", 0x0D, 0x0A, 0

TIMES 510 - ($ - $$) db 0
DW 0xAA55
