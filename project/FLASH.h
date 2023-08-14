#ifndef FLASH_H
#define FLASH_H

#include "LIB.h"
#include "MKL46Z4.h"

/*************************************************/
void ClearFlash(uint32 address);
void WriteFlash(uint32 address,uint16 data[]);
void WriteFlash4Byte(uint32 address,uint32 data);

/********************** PROTOTYPE ************************/

#endif
