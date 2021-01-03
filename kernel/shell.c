#include "shell.h"


void enter_shell()
{
    print("Operating system Costa Version 1.0\n");
    print(">>"); 
    while(1)
    {
        while(NOT_KEY_EXECUTE){} // wait until we can process the data 

        key_buffer[--index] = 0;

        /***
         *  TODO: Create a command datastructure
         *  TODO: Create a parser for the commands
         */

        parse_command();


        clear_buffer();
        print(">> ");
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
            print("read disk : lire le contenu du disque\n");
            print("clear : nettoyer l'ecran\n");
            print("\n");
        }
        else if(COMMAND("lspci"))
        {
            device_scan();
            print("\n");
        }     
        else if(COMMAND("read disk"))
        {
            read_sectors_ATA_PIO(0,0,1);
            print("\n");
        }
        else if(COMMAND("clear"))
        {
            clear_screen();
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

    putch(input);

    key_buffer[index++] = input;
}
