#ifndef ATA_H
#define ATA_H

#include "../cpu/types.h"
#include "../drivers/screen.h"
#include "low_level.h"


void read_sectors_ATA_PIO(u32 target_address, u32 LBA, u8 sector_count);
void write_sectors_ATA_PIO(u32 LBA,u8 sector_count, u32* bytes);
#endif