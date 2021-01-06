print_string:
    pusha
    next:
    mov al, [bx] 
    cmp al, 0 
    je  continue_in_next 
    mov ah, 0x0e
    int 0x10 
    add bx, 1
    jmp next
    continue_in_next:
    popa
    ret

set_cursor_line:
    pusha
	mov dl, 0
	mov bh, 0
	mov ah, 2
    int 0x10
    popa
    ret

set_graphics_mode:
    mov al, 0x13
	mov ah, 0
	int 0x10

    mov ah, 1
    mov cx, 0x2607
    int 0x10
    ret