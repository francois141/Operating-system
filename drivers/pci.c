#include "pci.h"

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA    0xCFC

u32 pciConfigReadWord(u8 bus,u8 slot,u8 func,u8 offset){
    u32 address;
    u32 lbus  = (u32) bus;
    u32 lslot = (u32) slot;
    u32 lfunc = (u32) func;
    u16 tmp = 0;

    address = (u32) ( (lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((u32)0x80000000) );

    port_long_out(CONFIG_ADDRESS, address);

    return port_long_in(0xCFC);
}

u16 getVendorId(u8 bus,u8 slot,u8 func)
{
    return DEVICE_VENDOR_MASK(pciConfigReadWord(bus,slot,func,DEVICE_VENDOR_OFFSET));
}

u16 getDeviceId(u8 bus,u8 slot,u8 func)
{
    return DEVICE_ID_MASK(pciConfigReadWord(bus,slot,func,DEVICE_ID_OFFSET));
}

u8 getDeviceClassCode(u8 bus,u8 slot,u8 func)
{
    return DEVICE_CLASS_CODE_MASK(pciConfigReadWord(bus,slot,func,DEVICE_CLASS_CODE_OFFSET));
}

u8 getDeviceSubClassCode(u8 bus,u8 slot,u8 func)
{
    return DEVICE_SUBCLASS_CODE_MASK(pciConfigReadWord(bus,slot,func,DEVICE_SUBCLASS_CODE_OFFSET));
}


PCI_HEADER get_header(u8 bus, u8 slot, u8 function)
{
    PCI_HEADER out;

    out.classCode = getDeviceClassCode(bus,slot,function);
    out.subClass  = getDeviceSubClassCode(bus,slot,function);
    out.vendorId  = getVendorId(bus,slot,function);
    out.deviceId  = getDeviceId(bus,slot,function);

    return out;
}

void device_scan()
{
    int nbDevices = 0;
    for(u16 bus = 0;bus < 256;bus++)
    {
        for(u8 device = 0; device < 32;device++)
        {
            if(getVendorId(bus,device,0) != 0xffff)
            {
                print("Device Found ");
                print_word(getVendorId(bus,device,0));
                print(" ");
                print_word(getDeviceId(bus,device,0));
                print("\n");
            }
        }
    }
}