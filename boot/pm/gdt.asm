gdt_start:

null_descriptor:
    dq 0x0
code_descriptor:
    dw 0xffff ; First 16 bits of limit. 
    dw 0 ; 16 bits &  
    db 0 ; 8 bits = 24 bits of base.
    db 10011010b
    ; pre=1 (segments), priv=00 (ring), ty=1(code) 
    ; type flags: code = 1 (yes), conforming = 0 (no), 
    ; readable = 1 (yes), acc = 0 (managed by cpu)
    db 11001111b
    ; other flags + last four bits of limit
    db 0 ; last 8 bits of base
data_descriptor:
    dw 0xffff 
    dw 0
    db 0 
    db 10010010b ; data_desc has different type flags. 
    db 11001111b
    db 0 

gdt_end: ; help calculate size of the GDT DS. 

gdt_descriptor: ; descriptor that allows CPU to know attribs of GDT (6 byte desc)
    ; size (16 bit = 2 byte)
    ; address (32 bit = 4 byte)
    dw gdt_end - gdt_start - 1 ; size of gdt (indexed at 1)

    dd gdt_start ; start

CODE_SEG equ code_descriptor - gdt_start ; offset value for code. 
DATA_SEG equ data_descriptor - gdt_start ; offset value for data. 