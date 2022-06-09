[org 0x7c00]

xor ax, ax
mov ds, ax
cld 

mov ah, 0x02 ; Reading sector. 
mov al, 1 ; Read 63 sectors
mov ch, 0 ; start from cylinder 0 
mov cl, 2 ; the sector number 2.
mov dh, 0 ; head number 0. 

xor bx, bx 
mov es, bx
mov bx, 0x7e00 ; 512 bytes from the origin address

int 0x13 

mov ah, 0x0e
mov al, [bx]
int 0x10

inc bx
mov al, [bx]
int 0x10

inc bx
mov al, [bx]
int 0x10

; boilerplate bootloader instructions
jmp $
times 510 - ($-$$) db 0 
dw 0xaa55
; creating an extra sector after magic numbers. 
times 1 db 'B'
times 511 db 'A'
;times 512 db 'A'