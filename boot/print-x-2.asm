;
; A simple boot sector that prints a message to the screen using a BIOS routine.
;
mov ah, 0x0e ; int 10/ ah = 0eh -> scrolling teletype BIOS routine

; Third attempt
mov al,[0x7c09]
int 0x10
jmp $ ; Jump to the current address ( i.e. forever ).

the_secret:
db 'X'
;
; Padding and magic BIOS number.
;
times 510-($-$$) db 0 	; Pad the boot sector out with zeros
dw 0xaa55 					; Last two bytes form the magic number so BIOS knows we are a boot sector.
