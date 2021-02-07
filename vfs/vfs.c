#include "vfs.h"

#define MAGIC_WORD 0xbeeffeeb

const unsigned int *base_address = (u32*)0x200000;
const unsigned int *number_files = (u32*)0x200004;
const unsigned int base_lba = 100;

static int getFileInt(u8 number)
{
    return (base_address + 512 * (number + 1));
}


void parse_vfs()
{
    read_sectors((u32)base_address,100,3);

    int magic_word = *base_address;

    if(magic_word == MAGIC_WORD)
    {
        print("Found a file system : format EPF !\n\n");
    }
    else
    {
        print("PANIC");
        while(1){}
    }
    
    print("There are ");
    print_number((u32)*number_files);
    print(" files on the filesystem");
    print("\n\n");

    int *file_locations[2];
    file_locations[0] = base_address + 512/4;
    file_locations[1] = base_address + (512+512)/4;

    for(int i = 0; i < 2;i++)
    {
        print(file_locations[i]);
        print("\n");
    }

}

void read_file(int number)
{
    unsigned int *address = base_address + (512+512)/4 + 3;
    print("\n");
    print(address);
    print("\n");
}

static File* getFile(u8 number)
{
    File *file = (File*)(base_address + 512 * (number + 1));
    return file;
}

