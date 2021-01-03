all: os-image.bin

clean:
	rm  *.o
	rm  *.bin

run:
	qemu-system-x86_64 -fda os-image.bin
	
kernel.o: kernel/kernel.c
	gcc -ffreestanding  -m32 -fno-pie -c $< -o $@

low_level.o: drivers/low_level.c
	gcc -ffreestanding  -m32 -fno-pie -c $< -o $@

screen.o: drivers/screen.c
	gcc -ffreestanding  -m32 -fno-pie -c $< -o $@

system.o: system_lib/system.c
	gcc -ffreestanding  -m32 -fno-pie -c $< -o $@

boot_sect.bin: boot/bootloader.asm
	nasm  -f bin  $< -o $@

kernel_entry.o: boot/kernel_entry.asm
	nasm -f elf $< -o $@

kernel.bin: kernel_entry.o kernel.o low_level.o screen.o system.o
	ld -m elf_i386 -s -o $@  kernel.o kernel_entry.o low_level.o screen.o system.o -Ttext 0x01000  --oformat binary

os-image.bin: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin > os-image.bin



