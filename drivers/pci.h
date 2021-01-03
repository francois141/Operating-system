#ifndef PCI_H
#define PCI_H

#include "../cpu/types.h"
#include "../drivers/low_level.h"
#include "../drivers/screen.h"

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA    0xCFC

#define DEVICE_ID_OFFSET             0x0
#define DEVICE_VENDOR_OFFSET         0x0

#define DEVICE_CLASS_CODE_OFFSET     0x8
#define DEVICE_SUBCLASS_CODE_OFFSET  0x8

#define DEVICE_ID_MASK(x)            (x) & 0xFFFF     
#define DEVICE_VENDOR_MASK(x)        (x >> 16) & 0xFFFF

#define DEVICE_CLASS_CODE_MASK(x)    (x >> 24) & 0xFF
#define DEVICE_SUBCLASS_CODE_MASK(x) (x >> 16) & 0xFF

typedef struct
{
    struct PCI_HEADER *array;
    u16 NB_devices;
} DEVICE_LIST;

typedef struct
{
    u16 vendorId;
    u16 deviceId;
    u8  subClass;
    u8  classCode;
}__attribute__((packed)) PCI_HEADER;

u32 pciConfigReadWord(u8,u8,u8,u8);

u16 getVendorId(u8 bus,u8 slot,u8 func);
u16 getDeviceId(u8 bus,u8 slot,u8 func);

u8 getDeviceClassCode(u8 bus,u8 slot,u8 func);
u8 getDeviceSubClassCode(u8 bus,u8 slot,u8 func);

PCI_HEADER get_header(u8,u8,u8);
void device_scan();

#endif