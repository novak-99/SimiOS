#ifndef REGS_H
#define REGS_H

struct regs{
	unsigned int gs, fs, es, ds; // explicitly pushed by us
	unsigned int edi, esi, ebp, esp, ebx, ecx, edx, eax; // pusha does this 
	unsigned int int_no, err_code; // explicitly pushed by us
	unsigned int eip, cs, eflags, useresp, ss; // pushed by processor 
};

#endif
