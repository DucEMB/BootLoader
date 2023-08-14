#include "FLASH.h"

void ClearFlash(uint32 address)
{       
    if((address % 1024 == 0) && (address <= 0x3fffff))
    {
        while(FTFA->FSTAT != FTFA_FSTAT_CCIF_MASK);
        /* address */
        FTFA->FCCOB1 = ((address & 0xFF0000) >> 16);
        FTFA->FCCOB2 = ((address & 0xFF00) >> 8);
        FTFA->FCCOB3 = (address & 0xFF);
        /* command */
        FTFA->FCCOB0 = FTFA_FCCOB0_CCOBn(0x09);
        FTFA->FSTAT |= FTFA_FSTAT_CCIF(1);
        while(FTFA->FSTAT != FTFA_FSTAT_CCIF_MASK);
    }
}

void WriteFlash(uint32 address,uint16 data[])
{
    if((address % 4 == 0) && (address <= 0x3fffff) && (address >= 0x400))
    {
        while(FTFA->FSTAT != FTFA_FSTAT_CCIF_MASK);
        /* address */
        FTFA->FCCOB1 = (address >> 16);
        FTFA->FCCOB2 = (address >> 8);
        FTFA->FCCOB3 = (address);
        /* data */
        FTFA->FCCOB7 = data[0];
        FTFA->FCCOB6 = data[1];
        FTFA->FCCOB5 = data[2];
        FTFA->FCCOB4 = data[3];
        /* command */
        FTFA->FCCOB0 = FTFA_FCCOB0_CCOBn(0x06);
        FTFA->FSTAT |= FTFA_FSTAT_CCIF(1);
        while(FTFA->FSTAT != FTFA_FSTAT_CCIF_MASK);
    }
}

void WriteFlash4Byte(uint32 address,uint32 data)
{
    if(address % 4 == 0 && address <= 0x3fffff)
    {
        while((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0);
        /* address */
        FTFA->FCCOB1 = (address >> 16);
        FTFA->FCCOB2 = (address >> 8);
        FTFA->FCCOB3 = (address);
        /* data */
        FTFA->FCCOB4 = (data >> 24);
        FTFA->FCCOB5 = (data >> 16);
        FTFA->FCCOB6 = (data >> 8);
        FTFA->FCCOB7 = (data);
        /* command */
        FTFA->FCCOB0 = FTFA_FCCOB0_CCOBn(0x06);
        FTFA->FSTAT |= FTFA_FSTAT_CCIF_MASK;
        while((FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK) == 0);
    }
}