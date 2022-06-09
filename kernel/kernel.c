#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isrc.h"
#include "../cpu/irqc.h"

void main(){
	clear_screen(); 
	print("Hello, and Welcome to SimiOS!\n");
	idt_install();
	isrs_install();
	irq_install();
	__asm__("sti");
	
	keyboard_install();
}
