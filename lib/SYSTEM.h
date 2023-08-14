#ifndef SYSTEM_H
#define SYSTEM_H

#include "LIB.h"
#include "FLASH.h"
#include "UART.h"

/*************************************************/
#define GREEN_LED_ON        GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF       GPIOD->PSOR |= (1 << 5)
#define GREEN_LED_TOGGLE    GPIOD->PTOR |= (1 << 5)
#define RED_LED_ON          GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF         GPIOE->PSOR |= (1 << 29)
#define RED_LED_TOGGLE      GPIOE->PTOR |= (1 << 29)

/****************** DEFINITION **********************/

/*************************************************/
void BackUp();
void GetPC();
void SetPC(uint32 PC);
void GetMSP();
void SetMSP(uint32 MSP);
void PushVectorTableToRam();
void initLed();
void Restore();

/********************** PROTOTYPE ************************/
#endif
