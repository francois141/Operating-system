#ifndef ATA_H
#define ATA_H

#include "../cpu/types.h" 
#include "low_level.h"
#include "screen.h"

#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

#define uint32_t u32
#define uint16_t u16
#define uint8_t u8

static void ATA_wait_BSY();
static void ATA_wait_DRQ();

void read_sectors_ATA_PIO(uint32_t target_address, uint32_t LBA, uint8_t sector_count);


#endif