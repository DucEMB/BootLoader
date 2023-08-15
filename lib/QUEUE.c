#include "QUEUE.h"

/*******************************************************/
uint8 g_Front = 0;
uint8 g_Rear = 0;
QueueType g_Queue = {0};
uint8 temp[MAX_LENGTH];

/*********************** VARIABLE **********************/

__ramfunc uint8 QueueIsFull()
{
    if(g_Queue.count == 5)
    {
        return TRUE;
    }
    return FALSE;
}
/************************** Brief *********************************************
*
    Funtion used to check the Quese if full and return True of False
**
*******************************************************************************/

uint8 QueueIsEmpty()
{
    if(g_Queue.count == 0)
    {
        return TRUE;
    }
    return FALSE;
}
/************************** Brief *********************************************
*
    Funtion used to check the Quese if empty and return True of False
**
*******************************************************************************/

__ramfunc void PushData(uint8 data)
{
    static uint8 cnt = 0;
    g_Queue.QueueElement[g_Rear].data[cnt] = data;
    cnt++;
    if(data == '\r')
    {
        if(QueueIsFull() == FALSE)
        {
            g_Rear = (g_Rear + 1);
            if(g_Rear == MAX_SIZE)
            {
                g_Rear = 0;
            }
            g_Queue.count++;
        }
        cnt = 0;
    }    
}
/************************** Brief *********************************************
*
    Input: data want to push into Queue (unsigned char type)
    Funtion used to push data into Queue
**
*******************************************************************************/

DataType * GetAddress()
{
    return &g_Queue.QueueElement[g_Front];
}
/************************** Brief *********************************************
*
    Funtion used get the address of the head of the Queue and return it to get the
    data from it
**
*******************************************************************************/

void FreeElement()
{
    g_Front = (g_Front + 1) % MAX_SIZE;
    g_Queue.count--;
}
/************************** Brief *********************************************
*
    Funtion update the head of Queue after Getting the data from it
**
*******************************************************************************/
