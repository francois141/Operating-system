#include "shell.h"


void enter_shell()
{
    print("Operating system Costa Version 1.0\n");
    print(">>"); 
    while(1)
    {
        while(NOT_KEY_EXECUTE){} // wait until we can process the data 
        key_buffer[--index] = 0;
        parse_command();
        clear_buffer();
        print(">>");
    }    
}

static void parse_command()
{
        if(COMMAND("end"))
        {
            return;
        }
        else if(COMMAND("help"))
        {
            print("end : stopper le syteme\n");
            print("lspci : analyser PCI\n");
            print("clear : nettoyer l'ecran\n");
            print("version : donne la version de l'os\n");
            print("random :random number\n");
            print("play snake : Play snake\n");
            print("read : read first lba address\n");           
            print("malloc : allocate 10 bytes\n");
            print("read : allocate 4096 bytes aligned\n");
            print("ls : read the content of the filesystem \n");
            print("open : open the selected file\n");
            print("vesa : parse all vesa modes\n");
            print("memory : return the physical memory \n");
        }
        else if(COMMAND("memory")) // this function is hugly it's normal I am testing it
        {
            for(int i = 0; i < 512;i++)
            {
                char *pointer = 0x8000+i;
                print_byte(*pointer);
            }print("\n");
        }
        else if(COMMAND("vesa")) // This function is hugly it's normal I am testing it
        {             
            u32 *pointer = 0x100c;
            print_long(*pointer);
            print("\n");

            u16 *pointer2 = 0x1022;
            while(*pointer2 != 0xFFFF)
            {
                print_word(*pointer2);
                print("\n");
                sleep(100);
                pointer2 += 1;
            }
        }
        else if(COMMAND("random"))
        {
            print_byte(random());
            print("\n");
        }
        else if(COMMAND("play snake"))
        {
            start_snake();
        }
        else if(COMMAND("lspci"))
        {
            device_scan();
            print("\n");
        }     
        else if(COMMAND("clear"))
        {
            clear_screen();
            set_cursor_offset(0);
        }
        else if(COMMAND("version"))
        {
            print("Version 1.0.0 \n");
        }
        else if(COMMAND("read"))
        {
            read_sectors_ATA_PIO(0,0,1);
        }
        else if(COMMAND("malloc aligned"))
        {
            print_long(malloc_aligned(4096));
            print("\n");
        }
        else if(COMMAND("malloc"))
        {
            print_long(malloc(10));
            print("\n");
        }
        else if(COMMAND("ls"))
        {
            parse_vfs();
            print("\n");
        }
        else if(COMMAND("open"))
        {
            read_file(1);
            print("\n");
        }
        else
        {
            print("Command pas connue");
            print("\n");
        }
}

static void clear_buffer()
{
    while(index >= 0)
    {
        key_buffer[index] = 0;
        index--;
    }
    index = 0;
}

void add_key(char input)
{
    if(index >= 256){
        print("Error TOO MUCH KEY"); 
        return;
    }
    if(input == 0x8)
    {
        if(index == 0)
            return;
        remove_last_char();
        index--;
    }
    else if(input < 32 && input != 10)
    {
        return;
    }
    else
    {
        putch(input);
        key_buffer[index++] = input;
    }

}
