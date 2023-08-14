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

uint8 QueueIsEmpty()
{
    if(g_Queue.count == 0)
    {
        return TRUE;
    }
    return FALSE;
}

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

DataType * GetAddress()
{
    return &g_Queue.QueueElement[g_Front];
}

void FreeElement()
{
    g_Front = (g_Front + 1) % MAX_SIZE;
    g_Queue.count--;
}

