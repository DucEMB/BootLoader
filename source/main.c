#include "MKL46Z4.h"
#include "LIB.h"
#include "CLOCK.h"
#include "QUEUE.h"
#include "SRECORD.h"
#include "UART.h"
#include "FLASH.h"
#include "SYSTEM.h"

/*************************************************/
void BootLoader();
void Application();

/********************** PROTOTYPE ************************/

/**********************************************************
****CODE
**********************************************************/

void main()
{
    initLed();
    SystemCoreClockUpdate();
    if((GPIOC->PDIR & (1 << 3)) == 0)
    {
        BootLoader(); /* gap nut nhan SW1 se vao chuong trinh boot */
    }
    while(1)
    {
        Application();
    }
}
void Application()
{
    Restore();
    GetMSP();
    GetPC();
}

void BootLoader()
{
    uint8 flag = TRUE;
    DataType * Address;
    uint32 LineCount = 0;
    SetCoreClockPLL(FREQUENCY48MHZ);
    ConfigureUART(BAUDRATE_921600,FREQUENCY24MHZ);
    TransmiteString("BootLoader Ready To Use");
    TransmiteChar('\n');
    TransmiteChar('\r');
    PushVectorTableToRam();
    ClearFlash(0xa000);
    SystemCoreClockUpdate();
    while(flag == TRUE)
    {
        if(QueueIsEmpty() == FALSE)
        {
            Address = GetAddress();
            LineCount++;
            if(CheckSum(Address->data) == TRUE)
            {
                if(ParseLine(Address->data) == TRUE)
                {
                    TransmiteString("Boot Completed ");
                    GetMSP();
                    GetPC();                  
                }
                FreeElement();
            }
            else
            {
                TransmiteString("Error CheckSum In Line ");
                ConvertAndTransmite(LineCount);
                Restore();
                TransmiteString("Restore Completed ");
                TransmiteChar('\n');
                TransmiteChar('\r');
                flag = FALSE;
            }
        }
        if((UART0->S1 & UART0_S1_OR_MASK) == UART0_S1_OR_MASK)
        {
            TransmiteString("Overrun Error");
            Restore();
            TransmiteString("Restore Completed ");
            TransmiteChar('\n');
            TransmiteChar('\r');
        }
        if((UART0->S1 & UART0_S1_FE_MASK) == UART0_S1_FE_MASK)
        {
            TransmiteString("Framing Error");
            Restore();
            TransmiteString("Restore Completed ");
            TransmiteChar('\n');
            TransmiteChar('\r');
        }
    }
}

__ramfunc void UART0_IRQHandler()
{       
    uint8 data;
    if (UART0->S1 & UART_S1_RDRF_MASK)
    {
        data = UART0->D;
        PushData(data);
    }
}