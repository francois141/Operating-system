[org 0x7c00]
    ; load graphics mode
    call set_graphics_mode

    mov bp, 0x600
    mov sp,bp

    ; retrieve vesa informations
    mov ax, 0x4f00
    mov di, 0x1000

    int 0x10

    ; get the system memory map (1 entry for the moment because I am testing this feature)
    xor ebx,ebx
    xor bp,bp
    mov edx, 'PAMS'
    mov eax, 0xe820
    mov ecx, 24
    mov di, 0x2000
    int 0x15
    jc errore
    cmp ax, 0x0
    jne continue
errore:
    jmp $
nexte:
    inc bp
    add di,0x24
continue:
    mov edx,'PAMS'
    mov ecx, 24
    mov eax,0xe820
    int 0x15
    cmp ebx,0
    jne nexte

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

