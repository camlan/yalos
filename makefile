# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

# TODO : Make sources dep on all header files .
# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES :. c =. o}

ts := $(shell /bin/date "+%Y%m%d%H%M%S")

# Defaul build target
all: os-image

# Run bochs to simulate booting of our code .
#run: all
#bochs

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
os-image:boot/out/boot_loader.bin kernel/out/kernel.bin 
	cat $^ > ~/os-run/os_image_$(ts).img
	echo "floppya : 1 _44 = d:\os-run\os_image_$(ts).img , status = inserted" > ~/os-run/bochsrc-1.bxrc
	echo "boot : a" >>  ~/os-run/bochsrc-1.bxrc

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main () in our kernel
# - the compiled C kernel
#kernel.bin: kernel/kernel_entry.o ${OBJ} ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
#%.o: %.c ${HEADERS} gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry .
#%.o: %.asm nasm $< -f elf -o $@
	
boot/out/boot_loader.bin:
	nasm boot/boot-kernel.asm -f bin -o boot/out/boot_loader.bin -i boot
	
kernel/out/kernel.bin: kernel_entry.o	
	gcc -ffreestanding -m32 -fno-pie -c kernel/clear_screen.c -c kernel -o kernel/out/clear_screen.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/get_cursor.c -c kernel -o kernel/out/get_cursor.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/get_screen_offset.c -c kernel -o kernel/out/get_screen_offset.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/handle_scrolling.c -c kernel -o kernel/out/handle_scrolling.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/low_level.c -c kernel -o kernel/out/low_level.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/memory_copy.c -c kernel -o kernel/out/memory_copy.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/print.c -c kernel -o kernel/out/print.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/print_at.c -c kernel -o kernel/out/print_at.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/print_char.c -c kernel -o kernel/out/print_char.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/set_cursor.c -c kernel -o kernel/out/set_cursor.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/low_level.c -c kernel -o kernel/out/low_level.o
	gcc -ffreestanding -m32 -fno-pie -c kernel/kernel-2.c -c kernel -o kernel/out/kernel.o
	
	ld -m elf_i386 --oformat binary -Ttext 0x1000 kernel/out/kernel_entry.o kernel/out/memory_copy.o kernel/out/get_cursor.o kernel/out/handle_scrolling.o kernel/out/set_cursor.o kernel/out/get_screen_offset.o kernel/out/print_char.o kernel/out/print_at.o kernel/out/print.o kernel/out/clear_screen.o kernel/out/low_level.o kernel/out/kernel.o -o kernel/out/kernel.bin

kernel_entry.o: 
	nasm kernel/kernel-entry.asm -f elf -i kernel -o kernel/out/kernel_entry.o

clean: rm -fr *.bin *.dis *.o  rm -fr kernel/out/*.o boot/*.bin drivers/*.o