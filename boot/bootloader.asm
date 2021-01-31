[org 0x7c00]
    ; load graphics mode
    call set_graphics_mode

    mov bp, 0x850
    mov sp,bp

    ;load kernel into memory
    mov bx, 0x8000
    mov dh,56

    call load_from_disk

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


    times 510 -($ - $$) db 0
    dw 0xaa55

