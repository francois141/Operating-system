# Operating_System


![alt text](example.jpeg)

## My Operating system written from scratch

This is my first operating system written from scratch. It is certainly not very powerful and it probably has several bugs but it allowed me to learn the basics of an operating system and drivers. I wrote it during my bachelor degree. This system is not intended to be functional or perfect. 

### Memory map in the RAM

| **Address** | **Memory map**                  |
|-------------|---------------------------------|
| 0x1000      | VESA information                |
| 0x2000      | Block for VESA mode             |
| 0x3000      | Available physical memory       |
| 0x8000      | Kernel Loader                   |
| 0x100000    | Kernel                          |
| 0x10000000  | Kernel stack pointer            |
| 0x10000000  | Malloc function of the kernel   |


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
* Snake ( When I am tired studying !! )
* Identity paging
* Basic ata driver
* Basic malloc function
* Basic virtual file system
* Global descriptor table 
* Retrieve VESA Information
* Retrieve the physical memory map
* Setting 1280 * 1024 resolution mode
* Retrieve physical memory map

### TODO

* Processes
* User mode
* Gui
* System lib
* Better disk driver
* File system
* Sound

### How to build it

You should have qemu, nasm, gcc & g++ installed on your computer. I tried my OS only on ubuntu. If you are on ubuntu and all dependencies are installed then write ./compile.sh on the terminal and it will run.

### Some ressouces that helped me 

http://www.jamesmolloy.co.uk/tutorial_html/index.html


