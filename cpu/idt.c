#include "idt.h"
#include "../kernel/util.h"

struct entry{
	unsigned short base_lo; 
	unsigned short sel; 
	unsigned char zero; 
	unsigned char flags; 
	unsigned short base_hi; 
} __attribute__((packed)); // Smallest possible allignment.

struct idt_ptr{
	unsigned short limit; 
	unsigned int base; 
} __attribute__((packed));

struct entry idt[256];
struct idt_ptr idtp; 

extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
	idt[num].base_lo = (short)(base & 0xffff);  
	idt[num].sel = sel; 
	idt[num].zero = 0; 
	idt[num].flags = flags; // eg, 0b10001110
	idt[num].base_hi = (short)(base >> 16);
}

void idt_install(){
	idtp.limit = sizeof(struct entry) * 256 - 1; // size. 
	idtp.base = &idt; // Starting address 
		
	memory_set(&idt, 0, sizeof(struct entry) * 256);
	// Initialize our IDT to 0s. 
	
	idt_load();
}
