# Automatically generate lists of srcs using wildcards. 

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
SPEC_ASM = $(wildcard boot/idt/*.asm)

OBJ = ${C_SOURCES:.c=.o} 
SPEC_OBJ = ${SPEC_ASM:.asm=.o}

# SOURCES main target.
all: os-image

os-image: boot/boot_sector.bin kernel.bin 
	cat $^ > $@

# Run qemu to simulate booting our code. 
run: all
	qemu-system-x86_64 os-image

# Build the kernel bin 
kernel.bin: kernel/kernel_entry.o ${OBJ} ${SPEC_OBJ}
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary 
	
# Build the kernel obj file 
%.o : %.c ${HEADERS}
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

# Build the kernel entry obj file 
%.o : %.asm
	nasm $< -f elf32 -o $@
	
# Boot sector bin file.
%.bin : %.asm
	nasm $< -f bin -o $@
	
# Clean main dev dir. 
clean: 
	rm -fr *.bin *.o *.dis os-image *.map
	rm -fr kernel/*.o boot/*.bin  cpu/*.bin drivers/*.o cpu/*.o
