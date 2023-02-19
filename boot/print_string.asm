print_string:
pusha ; begin 
mov ah, 0x0e ; int 10/ah = 0eh -> scrolling teletype BIOS routine

print_next:
mov al, [bx]
int 0x10
add bx, 0x1
mov cl, [bx]
cmp cl, 0x0
je the_end
jmp print_next

the_end:
; end
popa 
ret