CC=gcc
CFLAGS=-ffreestanding -m32 -fno-pie -c
LDFLAGS=-m elf_i386 --oformat binary -Ttext 0x1000
SOURCES = $(wildcard kernel/*.c)
OBJECTS=$(addprefix kernel/out/,$(notdir $(SOURCES:.c=.o)))
TS := $(shell /bin/date "+%Y%m%d%H%M%S")

# Defaul build target
all: os-image

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
# Later bochs config file is generated to boot with floppy with generated kernel
os-image:boot/out/boot_loader.bin kernel/out/kernel.bin 
	cat $^ > ~/os-run/os_image_$(TS).img
	echo "floppya : 1 _44 = d:\os-run\os_image_$(TS).img , status = inserted" > ~/os-run/bochsrc-1.bxrc
	echo "boot : a" >>  ~/os-run/bochsrc-1.bxrc

# Compile kernel 
kernel/out/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

# Assemble boot loader
boot/out/boot_loader.bin:
	nasm boot/boot-kernel.asm -f bin -i boot -o $@

# Link kernel entry binary with kernel modules
kernel/out/kernel.bin: kernel/out/kernel_entry.o $(OBJECTS)
	ld $(LDFLAGS) $^ -o $@

# Assemble the kernel_entry
kernel/out/kernel_entry.o: 
	nasm kernel/kernel-entry.asm -f elf -i kernel -o $@

clean: 
	rm -fr $(OBJECTS) boot/out/*.bin

.PHONY: all clean