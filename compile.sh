nasm boot/bootloader.asm -f bin -o boot_sect.bin
nasm boot/kernel_entry.asm -f elf -o kernel_entry.o

gcc -ffreestanding  -m32 -fno-pie -c kernel/kernel.c -o kernel.o
gcc -ffreestanding  -m32 -fno-pie -c drivers/low_level.c -o low_level.o
gcc -ffreestanding  -m32 -fno-pie -c drivers/screen.c -o screen.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/system.c -o system.o

gcc -ffreestanding  -m32 -fno-pie -c cpu/idt.c -o idt.o
gcc -ffreestanding  -m32 -fno-pie -c cpu/isr.c -o ist.o
gcc -ffreestanding  -m32 -fno-pie -c drivers/timer.c -o timer.o
gcc -ffreestanding  -m32 -fno-pie -c drivers/keyboard.c -o keyboard.o

gcc -ffreestanding  -m32 -fno-pie -c drivers/pci.c -o pci.o

gcc -ffreestanding  -m32 -fno-pie -c kernel/shell.c -o shell.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/string.c -o string.o

gcc -ffreestanding  -m32 -fno-pie -c system_lib/graphics/libgui.c -o libgui.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/math.c -o math.o

gcc -ffreestanding  -m32 -fno-pie -c drivers/pc_speaker.c -o pc_speaker.o
gcc -ffreestanding  -m32 -fno-pie -c games/snake.c -o snake.o
gcc -ffreestanding  -m32 -fno-pie -c cpu/paging.c -o paging.o
gcc -ffreestanding  -m32 -fno-pie -c drivers/ata.c -o ata.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/malloc.c -o malloc.o

gcc -ffreestanding  -m32 -fno-pie -c vfs/vfs.c -o vfs.o
gcc -ffreestanding  -m32 -fno-pie -c cpu/gdt.c -o gdt.o

nasm cpu/interrupt.asm -f elf -o interrupt.o
nasm cpu/gdt.asm       -f elf -o gdt_asm.o

ld -m elf_i386 -s -o kernel.bin -Ttext 0x8000  kernel_entry.o low_level.o \
  system.o screen.o interrupt.o  gdt.o gdt_asm.o idt.o ist.o pci.o ata.o math.o snake.o pc_speaker.o malloc.o vfs.o paging.o timer.o keyboard.o libgui.o shell.o string.o kernel.o --oformat binary -e 0x8000

cat boot_sect.bin kernel.bin > os-image.bin

cd vfs_builder
./build.sh
cd ..

dd if=vfs_builder/filesystem of=os-image.bin bs=512 seek=100 count=100

qemu-system-x86_64 -hda os-image.bin -soundhw pcspk -boot c

make clean