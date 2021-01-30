# Operating_System

## My Operating system written from scratch

This is my first operating system written from scratch. It is certainly not very powerful and it probably has several bugs but it allowed me to learn the basics of an operating system and drivers.

### Current features of the operating system 

* Protected mode
* Screen driver 
* Keyboard driver
* Pci driver
* Shell
* Timer & sleep_function
* Basic math library
* Basic graphics library
* Beep driver
* Snake
* Identity paging
* Basic ata driver
* Basic malloc function
* Basic virtual file system

### Next step

* Improve the bootloader & create a boot data structure to retrieve the informations
* Improve the malloc function
* Improve the vfs

### How to build it

You should have qemu, nasm, gcc & g++ installed on your computer. I tried my OS only on ubuntu. If you are on ubuntu and all dependencies are installed then write ./compile.sh on the terminal and it will run.