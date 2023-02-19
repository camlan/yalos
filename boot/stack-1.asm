[org 0x7c00]
mov ah, 0x0e ; int 10/ ah = 0eh -> scrolling teletype BIOS routine


mov bp, 0x8000
mov sp, bp ; loads our boot sector - so it won 't overwrite us.

push 'A' 
push 'B' 
push 'C'

pop bx 
mov al, bl 
int 0x10

pop bx 
mov al, bl 
int 0x10

pop bx 
mov al, bl 
int 0x10

mov al, [0x7ffe]
int 0x10

;
; Padding and magic BIOS number.
;
times 510-($-$$) db 0 	; Pad the boot sector out with zeros
dw 0xaa55 					; Last two bytes form the magic number so BIOS knows we are a boot sector.
