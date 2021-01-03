nasm boot/bootloader.asm -f bin -o boot_sect.bin
nasm boot/kernel_entry.asm -f elf -o kernel_entry.o

gcc -ffreestanding  -Werror -m32 -fno-pie -c kernel/kernel.c -o kernel.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c drivers/low_level.c -o low_level.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c drivers/screen.c -o screen.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c system_lib/system.c -o system.o

gcc -ffreestanding  -Werror -m32 -fno-pie -c cpu/idt.c -o idt.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c cpu/isr.c -o ist.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c cpu/timer.c -o timer.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c drivers/keyboard.c -o keyboard.o

gcc -ffreestanding  -Werror -m32 -fno-pie -c drivers/ata.c -o ata.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c drivers/pci.c -o pci.o

gcc -ffreestanding  -Werror -m32 -fno-pie -c kernel/shell.c -o shell.o
gcc -ffreestanding  -Werror -m32 -fno-pie -c system_lib/string.c -o string.o

nasm cpu/interrupt.asm -f elf -o interrupt.o

ld -m elf_i386 -s -o kernel.bin -Ttext 0x01000  kernel_entry.o low_level.o \
ata.o kernel.o system.o screen.o interrupt.o idt.o ist.o timer.o  pci.o keyboard.o shell.o string.o --oformat binary -e 0x1000

cat boot_sect.bin kernel.bin > os-image.bin

qemu-system-x86_64 -drive file=os-image.bin,format=raw 

make clean