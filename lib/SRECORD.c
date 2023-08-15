#include "SRECORD.h"

/*******************************************************/
uint8 g_CompleteFlag = FALSE;
uint8 g_Vector[100];

/*********************** VARIABLE **********************/

/**********************************************************
****CODE
**********************************************************/

uint8 Strlen(uint8 array[])
{
    uint8 cnt = 0;
    while((array[cnt] != '\r') && (array[cnt] != '\n'))
    {
        cnt++;
    }
    return cnt;
}
/*brief*/
char HexToDec(uint8 data)
{       
    char result;
    if((data >= '0') && (data <= '9'))
    {
        result = data - '0';
    }
    else if((data >= 'A' ) && ( data <= 'F'))
    {
        result = data - 'A' + 10;
    }
    else
    {
        result = -1;
    }
    return result;
}
/*brief*/
uint8 CheckSum(uint8 array[])
{
    uint32 sum = 0;
    uint8 i = 0;
    uint8 length = Strlen(array);
    for(i = 2;i < length - 1;i = i + 2)
    {
        sum += HexToDec(array[i])*16 + HexToDec(array[i+1]);
    }
    if((sum & 0xFF) == 0xFF)
    {
        return TRUE;
    }
    return FALSE;
}

uint8 CheckByteCount(uint8 array[])
{
    uint8 i = 0;
    uint8 Count = 0;
    uint8 ByteCount;
    ByteCount = (HexToDec(array[2])*16 + HexToDec(array[3]))*2;
    for(i = 4;i < Strlen(array);i++)
    {
        Count++;
    }
    if(Count == ByteCount)
    {
        return TRUE;
    }
    return FALSE;
}

uint8 ParseLine(uint8 temp[])
{
    uint8 length = Strlen(temp);
    uint32 address = 0;
    uint8 i = 0;
    uint16 tmp_data[4];
    if(temp[0] == 'S')
    {
        if(temp[1] == '1')
        {
            address = (HexToDec(temp[4]) << 12) | (HexToDec(temp[5]) << 8) \
            | (HexToDec(temp[6]) << 4) | (HexToDec(temp[7]));
            if(address == 0xa000)
            {
                for(i = 0;i < 100;i++)
                {
                    g_Vector[i] = temp[i];
                }
            }
            else 
            {
                for(i = 8;i < length - 8;i += 8)
                {
                    tmp_data[0] = (HexToDec(temp[i]) << 4) | HexToDec(temp[i+1]);
                    tmp_data[1] = (HexToDec(temp[i+2]) << 4) | HexToDec(temp[i+3]);
                    tmp_data[2] = (HexToDec(temp[i+4]) << 4) | HexToDec(temp[i+5]);
                    tmp_data[3] = (HexToDec(temp[i+6]) << 4) | HexToDec(temp[i+7]);
                    WriteFlash(address,tmp_data);
                    address += 4;    
                }
            }
        }
        else if(temp[1] == '2')
        {
            address = (HexToDec(temp[4]) << 20 ) | (HexToDec(temp[5]) << 16) \
            | (HexToDec(temp[6]) << 12) | (HexToDec(temp[7]) << 8) | (HexToDec(temp[8]) << 4)\
            | (HexToDec(temp[9]));
            if(address == 0xa000)
            {
                for(i = 0;i < 100;i++)
                {
                    g_Vector[i] = temp[i];
                }
            }
            else
            {
                for(i = 10;i < length - 8;i += 8)
                {
                    tmp_data[0] = (HexToDec(temp[i]) << 4) | HexToDec(temp[i+1]);
                    tmp_data[1] = (HexToDec(temp[i+2]) << 4) | HexToDec(temp[i+3]);
                    tmp_data[2] = (HexToDec(temp[i+4]) << 4) | HexToDec(temp[i+5]);
                    tmp_data[3] = (HexToDec(temp[i+6]) << 4) | HexToDec(temp[i+7]);
                    WriteFlash(address,tmp_data);
                    address += 4;
                }
            }
        }
        else if((temp[1] == '9') || (temp[1] == '8'))
        {
            g_CompleteFlag = TRUE;          
        }
    }
    if(g_CompleteFlag == TRUE)
    {
        length = Strlen(g_Vector);
        address = 0xa000;
        for(i = 8;i < length - 8;i += 8)
        {
            tmp_data[0] = (HexToDec(g_Vector[i]) << 4) | HexToDec(g_Vector[i+1]);
            tmp_data[1] = (HexToDec(g_Vector[i+2]) << 4) | HexToDec(g_Vector[i+3]);
            tmp_data[2] = (HexToDec(g_Vector[i+4]) << 4) | HexToDec(g_Vector[i+5]);
            tmp_data[3] = (HexToDec(g_Vector[i+6]) << 4) | HexToDec(g_Vector[i+7]);
            WriteFlash(address,tmp_data);
            address += 4;    
        }
        BackUp();
    }
    return g_CompleteFlag;
}
