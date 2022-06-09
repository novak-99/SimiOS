#include "irqc.h"
#include "../kernel/low_level.h"

extern void irq0();
extern void irq1(); 
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5(); 
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = 
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

void irq_install_handler(int irq, void (*handler)(struct regs *r)){
	irq_routines[irq] = handler; // IRQ handler for stated IRQ. 
}

void irq_uninstall_handler(int irq){
	irq_routines[irq] = 0;
}


// irq_remap 
void irq_remap(void){
	// 0x20: PICM CMD
	// 0x21: PICM Data
	
	// 0xA0: PICS CMD
	// 0xA1: PICS Data
	
	// NOTE HERE: 

	port_byte_out(0x20, 0x11); // Initialize (ICW1) PICM
	port_byte_out(0xA0, 0x11); // Initialize (ICW1) PCIS
	
	port_byte_out(0x21, 0x20); // Remap PICM to 0x20 (32 decimal)
	port_byte_out(0xA1, 0x28); // Remap PCIS to 0x28 (40 decimal)
	
	port_byte_out(0x21, 0x04); // IRQ2 (0x04) -> Connecting to slave
	port_byte_out(0xA1, 0x02);
	
	port_byte_out(0x21, 0x01); // ICW4 to PICM 
	port_byte_out(0x21, 0x01); // ICW4 to PICS
	
	port_byte_out(0x21, 0x0); // Enable all IRQs on PICM
	port_byte_out(0xA1, 0x0); // Enable all IRQs on PICS
}

void irq_install(){
	irq_remap(); 
	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E); 
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E); 
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E); 
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E); 
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E); 
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E); 
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E); 
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E); 
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E); 
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E); 
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E); 
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E); 
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E); 
}

void irq_handler(struct regs *r){
	void (*handler)(struct regs *r); 
	handler = irq_routines[r->int_no - 32]; 
	if(handler){
		handler(r); 
	}
	
	if(r->int_no >= 40){ // send EOI to slave controller, loc at 0xA0.
		port_byte_out(0xA0, 0x20);	
	}
	
	port_byte_out(0x20, 0x20); // Send EOI to master controller, loc at 0x20. 
}






