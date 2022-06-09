#define IRQ1 1 // IRQ 1 corresponds to the keyboard device.  
#include "../cpu/regs.h"

void keyboard_handler(struct regs *r);
void scan_code_handler(unsigned char scan_code);
void text_col_handler(); 
void keyboard_install(); 
