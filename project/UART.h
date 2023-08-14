#ifndef UART_H
#define UART_H

#include "MKL46Z4.h"
#include "LIB.h"

/*************************************************/
void ConfigureBaudrate(uint32 Baudrate,uint32 ClockFrequency);
void ConfigureUART(uint32 Baudrate,uint32 Frequency);
void TransmiteString(uint8 a[]);
void TransmiteChar(uint8 a);
void ConvertAndTransmite(uint32 LineCnt);

/********************** PROTOTYPE ************************/
#endif
