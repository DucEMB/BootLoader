#ifndef SRECORD_H
#define SRECORD_H

#include "LIB.h"
#include "FLASH.h"
#include "SYSTEM.h"
#include "QUEUE.h"

/*************************************************/
uint8 Strlen(uint8 array[]);
uint8 CheckSum(uint8 array[]);
char HexToDec(uint8 data);
uint8 ParseLine(uint8 temp[]);

/********************** PROTOTYPE ************************/
#endif
