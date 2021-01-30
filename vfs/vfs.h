#ifndef VFS_H
#define VHS_H

#include "../drivers/screen.h"
#include "../drivers/ata.h"

// It's the most basic filesystem I can write 
typedef struct File{
    char title[12]; // Simple metadata 
    char data[500]; // Some data of course
}__attribute__((packed)) File;

void parse_vfs();
static File* getFile(u8);
void read_file(int);



#endif