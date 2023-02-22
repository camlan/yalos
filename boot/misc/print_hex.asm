print_hex:
pusha
mov ax, dx
and ax, 0x000f
push ax

mov ax, dx
and ax, 0x00f0
shr ax, 0x0004
push ax

mov ax, dx
and ax, 0x0f00
shr ax, 0x0008
push ax

mov ax, dx
and ax, 0xf000
shr ax, 0x000c
push ax

mov cx, 0x04
print_loop:
pop ax

cmp ax, 0x09
jg letter_shift

number_shift:
add ax, 0x30
jmp end_shift

letter_shift:
add ax, 0x57 
end_shift:

mov ah, 0x0e ; Teletext mode
int 0x10
loop print_loop
 
end_print_hex:
; end
popa 
ret 
