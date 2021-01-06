[org 0x7c00]
    ; load graphics mode
    call set_graphics_mode

    ;load welcome message
    mov dh,0
    call set_cursor_line
    mov bx,boot_message
    call print_string

    ;load loading disk message
    mov dh,1
    mov bx,load_disk_message
    call set_cursor_line
    call print_string

    mov bp, 0x9000
    mov sp,bp



    ;load kernel into memory
    mov bx, 0x1000
    mov dh,50

    call load_from_disk

    ;print load the 32 bit mode
    mov dh,3
    call set_cursor_line  
    mov bx,load_32bit_mode
    call print_string
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
    call print_string_pm
    call 0x1000
    jmp $

[bits 16]


    times 510 -($ - $$) db 0
    dw 0xaa55

