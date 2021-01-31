[bits 32]
[global gdt_flush]

gdt_flush:
    mov eax,[esp+4] ; Load the pointer to the new table
    lgdt [eax]      ; Load the descriptor table
    mov ax, 0x10    ; offset for all segments
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush ; Far jump 
.flush:
    ret