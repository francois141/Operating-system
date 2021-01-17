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
            print("random : Genere un nombre aleatoire entre 0 et 49\n");
            print("play snake : Play snake\n");
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
