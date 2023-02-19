;
; A boot sector that prints a hex of value
;
[org 0x7c00] ; Tell the assembler where this code will be loaded


mov dx, 0x0fa1
mov bx, HEX_OUT
call print_hex_mem
call print_string

jmp $ 					; Hang

%include "print_hex_mem.asm"
%include "print_string.asm"

; Data

; global variables
HEX_OUT: db '0x0000',0

;
; Padding and magic BIOS number.
;
times 510-($-$$) db 0 	
dw 0xaa55