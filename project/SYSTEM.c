#include "SYSTEM.h"

/*******************************************************/
uint32 g_VectorTable[48]  __attribute__ ((aligned (0x100)));

/*********************** VARIABLE **********************/

/**********************************************************
****CODE
**********************************************************/

void initLed()
{
    /* Enable clock for PORTD, PORTE */
    SIM->SCGC5 |= (1 << 11);/* Set bit 11 enable clock portC*/
    SIM->SCGC5 |= (1 << 12);/* Set bit 12 enable clock portD*/
    SIM->SCGC5 |= (1 << 13);/* Set bit 13 enable clock portE*/
    
    /* Configure multiplex of PTD5 and PTE29 and PTC3 as GPIO */
    PORTD->PCR[5]  |= PORT_PCR_MUX(1);
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    PORTC->PCR[3]  |= PORT_PCR_MUX(1);
    PORTC->PCR[12]  |= PORT_PCR_MUX(1);
    
    // set up ngat theo suon xuong
    PORTC->PCR[3]  |= PORT_PCR_IRQC(10);
    PORTC->PCR[3]  |=3;
    PORTC->PCR[12]  |=3;
    
    /* Configure PTD5 and PTE29 as output, PTC3 as input  */
    GPIOD->PDDR |= (1 << 5);
    GPIOE->PDDR |= (1 << 29);
    GPIOC->PDDR &= (~(1 << 3));
    
    /* Clear PTD5 and PTE29 */
    RED_LED_OFF;
    GREEN_LED_OFF;
}

void SetPC(uint32 PC)
{
    __asm("BLX R0");
}

void GetPC()
{
    uint32 PC;
    uint32 * AddressPC;
    AddressPC = (uint32 *)0xa004;
    PC = * AddressPC;
    SetPC(PC);
}

void GetMSP()
{
    uint32 MSP;
    uint32 * AddressMSP;
    AddressMSP = (uint32 *)0xa000;
    MSP = * AddressMSP;
    SetMSP(MSP);
}

void Restore()
{
    uint32* StartAddress =(uint32 *)0xd000;
    uint32* EndAddrss = (uint32 *)0xe000;
    uint32 BackupBuffer = 0xa000;
    uint32 data;
    while(StartAddress < EndAddrss)
    {
        data = *StartAddress;
        WriteFlash4Byte(BackupBuffer,data);
        StartAddress++;
        BackupBuffer += 4;
    }
}

void BackUp()
{
    uint32* StartAddress =(uint32 *)0xa000;
    uint32* EndAddrss = (uint32 *)0xb000;
    uint32 BackupBuffer = 0xd000;
    uint32 data;
    while(StartAddress < EndAddrss)
    {
        data = *StartAddress;
        WriteFlash4Byte(BackupBuffer,data);
        StartAddress++;
        BackupBuffer += 4;
    }
    TransmiteString("Back Up Completed");
    TransmiteChar('\n');
    TransmiteChar('\r');
}

void SetMSP(uint32 MSP)
{
    __asm("MSR PSP, R0");
}

void PushVectorTableToRam()
{
    uint32 * address;
    address = (uint32 *)0x00000000;
    uint8 i;
    for(i = 0;i < 48;i++)
    {
        g_VectorTable[i] = * address;
        address++;
    }
    __asm("CPSID   I");
    SCB->VTOR = (uint32)g_VectorTable;
    __asm("CPSIE   I");
}
