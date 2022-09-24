#compile the kernel
nasm boot/bootloader.asm   -f bin -o boot_sect.bin
nasm boot/kernel_entry.asm -f elf -o kernel_entry.o
nasm cpu/interrupt.asm     -f elf -o interrupt.o
nasm cpu/gdt.asm           -f elf -o gdt_asm.o
nasm cpu/helpers.asm       -f elf -o helpers.o

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
gcc -ffreestanding  -m32 -fno-pie -c kernel/early_memory.c -o early_memory.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/linkedlist.c -o linkedlist.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/graphics/color.c -o color.o
gcc -ffreestanding  -m32 -fno-pie -c cpu/task.c -o task.o
gcc -ffreestanding  -m32 -fno-pie -c system_lib/algorithms/sort.c -o sort.o
#link the kernel
ld -m elf_i386 -s -o kernel.bin -Ttext 0x100000  kernel_entry.o low_level.o \
  system.o screen.o interrupt.o early_memory.o gdt.o gdt_asm.o idt.o color.o \
  ist.o linkedlist.o pci.o ata.o math.o snake.o pc_speaker.o malloc.o vfs.o \
  paging.o timer.o keyboard.o libgui.o shell.o task.o string.o helpers.o sort.o kernel.o --oformat binary -e 0x100000

#prepare the kernel loader
nasm boot_second/kernelloaderentry.asm -f elf -o kernelloaderentry.o
gcc -ffreestanding  -m32 -fno-pie -c boot_second/kernelloader.c -o kernelloader.o
ld -m elf_i386 -s -o kernelloader.bin -Ttext 0x8000 kernelloaderentry.o kernelloader.o --oformat binary -e 0x8000

#build the filesystem
cd vfs_builder
./build.sh
cd ..

#build the image
dd if=/dev/zero               of=os-image.bin seek=0    count=200   bs=512
dd if=boot_sect.bin           of=os-image.bin seek=0    count=1     bs=512 
dd if=kernelloader.bin        of=os-image.bin seek=1    count=4     bs=512 
dd if=kernel.bin              of=os-image.bin seek=5    count=80    bs=512
dd if=vfs_builder/filesystem  of=os-image.bin seek=100  count=100   bs=512  

#run the emulator
qemu-system-x86_64 -hda os-image.bin -soundhw pcspk -boot c -m 6G

#clean the files
make clean