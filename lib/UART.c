#include "UART.h"

/**********************************************************
****CODE
**********************************************************/

void ConfigureBaudrate(uint32 Baudrate,uint32 ClockFrequency)
{
    uint8 SystemOSR = 0;
    uint32 SystemSBR = 0;
    uint8 OSR;
    uint8 OSR1;
    uint32 SBR = 0;
    uint32 SBR1 = 0;
    uint32 Delta = 0;
    uint32 PreDelta = 1000000;
    uint32 Div = ClockFrequency / Baudrate;
    for(OSR = 31;OSR >= 3;OSR--)
    {   
        OSR1 = OSR + 1;
        SBR = Div / OSR1;
        SBR1 = (Div / OSR1) + 1;
        Delta = (ClockFrequency / (SBR * OSR1)) - Baudrate;
        if(Delta < PreDelta)
        {
            SystemOSR = OSR;
            SystemSBR = SBR;
            PreDelta = Delta;
        }
        Delta = Baudrate - (ClockFrequency / (SBR1 * OSR1));
        if(Delta < PreDelta)
        {
            SystemOSR = OSR;
            SystemSBR = SBR1;
            PreDelta = Delta;
        }
    }
    if(SystemSBR <= 255)
    {
        UART0->C4 = UART0_C4_OSR(SystemOSR);/* Configure Baudrate */
        UART0->BDL = UART0_BDL_SBR(SystemSBR);
    }
    else
    {
        UART0->C4 = UART0_C4_OSR(SystemOSR);
        UART0->BDL |= UART0_BDL_SBR(SystemSBR);
        UART0->BDH |= UART0_BDH_SBR((SystemSBR >> 8));
    }
}
/************************** Brief *********************************************
*
    Input:  +Baudrate (unsigned long type)
            +Clock source of the UART module(System Core Clock / 2)
    Funtion used to Configure the UART with the Baudrate that user want
**
*******************************************************************************/

void ConfigureUART(uint32 Baudrate,uint32 Frequency)
{
    /* Configure UART0 and PORTA to use */
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; /*Enable Clock for UART0 */
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Enable Clock for PORT A */
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); /*Select Source Clock for UART0 as Fll or PLL */
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select as PLL -> Frequency for UART0 is ClockFrequency / 2 */
    PORTA->PCR[1] |= PORT_PCR_MUX(2);/* Configure PORTA to use */
    PORTA->PCR[2] |= PORT_PCR_MUX(2);
    ConfigureBaudrate(Baudrate,Frequency);
    UART0->C2 |= UART0_C2_TE_MASK; /* Enable Transmitter */
    UART0->C2 |= UART0_C2_RE_MASK;
    NVIC_EnableIRQ(UART0_IRQn);        /* Enable interrupt for UART0 */
    UART0->C2 |= UART_C2_RIE_MASK;      /* Allow the interrupt receive data */
}
/************************** Brief *********************************************
*
    Input:  +Baudrate (unsigned long type)
            +Clock source of the UART module(System Core Clock / 2)
    Funtion used to Configure the UART with the Baudrate that user want
**
*******************************************************************************/

void TransmiteString(uint8 a[])
{
    uint8 i = 0;
    while(a[i] != '\0')
    {
        TransmiteChar(a[i]);
        i++;
    }
}
/************************** Brief *********************************************
*
    Funtion used to Transmite a string (array in unsigned char type)
**
*******************************************************************************/

void TransmiteChar(uint8 a)
{
    while((UART0->S1 & UART0_S1_TDRE_MASK) == 0);
    UART0->D = a;
}
/************************** Brief *********************************************
*
    Funtion used to Transmite a character
**
*******************************************************************************/

void ConvertAndTransmite(uint32 LineCnt)
{
    uint8 temp[10];
    uint8 digit;
    uint8 n = 0;
    int i;
    while(LineCnt > 0)
    {
        digit = LineCnt % 10;
        LineCnt /= 10;
        temp[n] = digit;
        n++;
    }
    for(i = n-1;i >= 0;i--)
    {
        TransmiteChar(temp[i] + '0');
    }
    TransmiteChar('\n');
    TransmiteChar('\r');
}
/************************** Brief *********************************************
*
    Input:  +data (unsigned long type)
    Funtion used to convert and transmite a format number
**
*******************************************************************************/
