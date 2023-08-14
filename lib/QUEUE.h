#ifndef QUEUE_H
#define QUEUE_H

#include "LIB.h"
#include "UART.h"
/*************************************************/
#define MAX_SIZE    5u
#define MAX_LENGTH  100u

typedef struct
{
    uint8 data[MAX_LENGTH];
}DataType;

typedef struct
{
    uint8 count;
    DataType QueueElement[MAX_SIZE];
}QueueType;

/****************** DEFINITION **********************/

/*************************************************/
__ramfunc uint8 QueueIsFull();
uint8 QueueIsEmpty();
__ramfunc void PushData(uint8 data);
DataType * GetAddress();
void FreeElement();

/********************** PROTOTYPE ************************/
#endif
