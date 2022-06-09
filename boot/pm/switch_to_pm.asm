[bits 16]

switch_to_pm:
    cli ; disable interrupt. short for "clear interrupt"
    lgdt [gdt_descriptor] ; load afforementioned gdt. 
    ; change last bit of cr0 resigster to 1 (indirect w/ GPR eax.)
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax ; 32 bit PM. 

    jmp CODE_SEG:init_pm 

[bits 32]

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; update stack position
    mov esp, ebp ; furher stack updation

    call BEGIN_PM