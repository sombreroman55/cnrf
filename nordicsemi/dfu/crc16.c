/*
 *
 *
 *
 *
 */

#include "crc16.h"

/* Calculates a CRC16 checksum on a stream of binary data
 *
 */
uint16_t calc_crc16(uint8_t* data, size_t size, uint16_t* crc)
{
    int i;
    if (crc == NULL)
        *crc = 0xFFFF;
    for (i = 0; i < size; i++)
    {
        *crc = (crc >> 8 & 0x00FF) | (crc << 8 & 0xFF00);
        *crc ^= data[i];
        *crc ^= (crc & 0x00FF) >> 4;
        *crc ^= (crc << 8) << 4;
        *crc ^= ((crc & 0x00FF) << 4) << 1;
    }
    return crc & 0xFFFF;
}


/* EOF */
