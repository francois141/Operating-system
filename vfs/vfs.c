#include "vfs.h"

#define MAGIC_WORD 0xbeeffeeb

const unsigned int *base_address = (u32*)0x100000;
const unsigned int *number_files = (u32*)0x100004;
const unsigned int base_lba = 100;

void parse_vfs()
{
    read_sectors((u32)base_address,100,3);

    int magic_word = *base_address;

    if(magic_word == MAGIC_WORD)
    {
        print("Found a file system : format EPF !\n");
    }
    else
    {
        print("PANIC");
        while(1){}
    }
    
    print("There are ");
    print_number((u32)*number_files);
    print(" files on the filesystem");

    for(int i = 0; i < *number_files;i++)
    {
        File *file = getFile(i);
        print(file->title);
        print("\n");
        print(file->data);
        print("\n");
    }
}

static File* getFile(u8 number)
{
    File *file = (File*)(base_address + 512 * (number + 1));
    return file;
}

