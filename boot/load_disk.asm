load_from_disk:
    pusha
    push dx

    mov ah,0x02 ; Bios lecture cd

    mov al,dh  ; Lire dh secteurs
    mov ch,0x00; Choisir Cylindre 0
    mov dh,0x00; Choisir Tete 0
    mov cl,0x02; Commencer à lire le secteur 2
    
    int 0x13
    jc disk_error

    pop dx
    cmp al,dh
    jne disk_error

    mov dh,2
    mov bx,load_disk_sucess
    call set_cursor_line
    call print_string

    popa
    ret
disk_error:
    mov dh,2
    mov bx,load_disk_fail
    call set_cursor_line
    call print_string
    jmp $
