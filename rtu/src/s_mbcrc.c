/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/rtu/src/s_mbcrc.c $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/


/* ----------------------- Platform includes --------------------------------*/
//#include "port.h"
//#include "stm8s_type.h"
#include "s_mbcrc.h"

/*******************************************************************************
 * @brief Calculate CRC16-Modbus. E.g. 0x0a03024152 -> CRC -> 0x28AC
 * @param pucFrame: pointer to Frame
 * @param usLen: Length of Frame excl. CRC
 * @retval usCRC
 *******************************************************************************/
uint16_t usMBCRC16(uint8_t *pucFrame, uint16_t usLen)
{
  uint16_t usCRC = 0xFFFF;
  uint8_t  uci;
  uint8_t  usFrameIdx;

  //loop through each byte in pucFrame
  for(usFrameIdx=0; usFrameIdx < usLen; usFrameIdx++)
  {
    //XOR byte into least significant byte of CRC
    usCRC ^= (uint16_t)pucFrame[usFrameIdx];

    // Loop over each bit
    for(uci=0; uci < 8; uci++)
    {
      if((usCRC & 0x0001) != 0)   // If the LSB is set
      {
        usCRC >>= 1;      // Right shift
        usCRC ^= 0xA001;  // XOR with 0xA001
      }
      else                // Else LSB is not set
      {
        usCRC >>= 1;      // Just shift right
      }
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return usCRC;
}






