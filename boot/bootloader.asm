[org 0x7c00]
    ; Explicitly set DS and ES to 0. Don't rely on the bootloader
    xor ax, ax     
    mov ds, ax
    mov es, ax

    ; load graphics mode
    call set_graphics_mode

    ; Setup a new stack address
    mov bp, 0x600
    mov sp,bp

    ; Enable A20
    mov ax,0x2401    
    int 0x15

    ; retrieve vesa informations
    mov ax, 0x4f00
    mov di, 0x1000
    int 0x10

    ; check if extension present
    mov ah, 0x41
    mov dl, 0x80
    mov bx, 0x55aa
    int 0x13
    jc end

    ; load the disk right now
    mov ah,0x42
    mov dl,0x80 
    mov si,structure
    int 0x13
    jc end

    ; switch to 32 bits protected mode
    call switch_to_pm
end:
    jmp end ;end

%include "boot/load_disk.asm"
%include "boot/messages.asm"
%include "boot/gdt.asm"
%include "boot/switch.asm"
%include "boot/print_string.asm"
%include "boot/print_string_32.asm"

[bits 32]
START_PM:
    mov ebx, load_kernel_msg
    mov ebp, 0x90000
    mov esp,ebp
    call print_string_pm
    call 0x8000
    jmp $

[bits 16]

structure:
    db 0x10
    db 0x0
    dw 0x0050
    dw 0x8000; offset
    dw 0x0000; segment
    dq 0x0000000000000001 ; Lba start

    times 510 -($ - $$) db 0
    dw 0xaa55

