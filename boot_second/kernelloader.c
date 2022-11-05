#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;

#define uint32_t u32
#define uint16_t u16
#define uint8_t u8

static void ATA_wait_BSY();
static void ATA_wait_DRQ();
static unsigned char port_byte_in(unsigned short port);
static void port_byte_out(unsigned short port, unsigned char data);
static unsigned short port_word_in(unsigned short port);
void read_sectors(uint32_t target_address, uint32_t LBA, uint8_t sector_count);

const u32 kernel_start_address = 0x100000;

void load_kernel()
{
    read_sectors(kernel_start_address,5,100);

    for(int i = 0; i < 10;i++)
    {
        u32*a = 0xa0000+i;
        *a = i % 40;
    }
    void (*jump_kernel)() = kernel_start_address;
    jump_kernel();
}


void read_sectors(uint32_t target_address, uint32_t LBA, uint8_t sector_count)
{
	ATA_wait_BSY();
	port_byte_out(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	port_byte_out(0x1F2,sector_count);
	port_byte_out(0x1F3, (uint8_t) LBA);
	port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
	port_byte_out(0x1F5, (uint8_t)(LBA >> 16)); 
	port_byte_out(0x1F7,0x20); //Send the read command

	uint16_t *target = (uint16_t*) target_address;

	for (int j =0;j<sector_count;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(int i=0;i<256;i++)
			target[i] = port_word_in(0x1F0);
		target+=256;
	}
}

static void ATA_wait_BSY()   //Wait for bsy to be 0
{
	while(port_byte_in(0x1F7)&STATUS_BSY);
}

static void ATA_wait_DRQ()  //Wait fot drq to be 1
{
	while(!(port_byte_in(0x1F7)&STATUS_RDY));
}

static unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result):"d"(port));
    return result;
}

static void port_byte_out(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port) );
}

static unsigned short port_word_in(unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}