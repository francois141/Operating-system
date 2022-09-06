[org 0x7c00]
    ; Explicitly set DS and ES to 0. Don't rely on the bootloader
    xor ax, ax     
    mov ds, ax
    mov es, ax
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
    ; get VBE mode information
    mov ax,0x4f01
    mov cx,0x4118
    mov di,0x2000
    int 0x10
    ; set VBE mode
    mov ax,0x4f02
    mov bx,0x411B
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

    ; get the physical memory map
    xor ebx,ebx
    xor bp,bp
    mov edx, 'PAMS'
    mov eax, 0xe820
    mov ecx, 24
    mov di, 0x3000
    int 0x15
    jc errore
    cmp eax,'PAMS'
    je continue
    
errore:
    jmp $
nexte:
    inc bp
    add di,24
continue:
    mov edx,'PAMS'
    mov ecx, 24
    mov eax,0xe820
    int 0x15
    cmp ebx,0
    jne nexte
    ; end of get the system memory

    ; switch to 32 bits protected mode (we are done with the bootloader stuff)
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
    mov ebp, 0x10000000 ; Move the kernel stack to this point in memory
    mov esp,ebp
    call print_string_pm
    call 0x8000 ; we call the kernel loader
    call 0x100000
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

