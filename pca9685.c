/*
 * @brief  PCA9685
 *
 * @note
 * Copyright (C) 2013-2014 Leonid Lezner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "pca9685.h"
#include "i2c.h"
   
/*****************************************************************************
* Private types/enumerations/variables
****************************************************************************/

static struct
{
  uint8_t address;
} PCA9685_Data;

/*****************************************************************************
* Public types/enumerations/variables
****************************************************************************/

/*****************************************************************************
* Private functions
****************************************************************************/

/*****************************************************************************
* Public functions
****************************************************************************/

result_t PCA9685_Init(void)
{
  int i;
  uint8_t mode1;
  
  /* Send a SWRST command */
  if(I2C_Write8(DEFAULT_I2C, 0x00, PCA9685_CMD_SWRST) != NO_ERROR)
  {
    return IO_ERROR;
  }
  
  mode1 = 0x21; /* Switch to normal mode, auto increment on */
  
  if(I2C_WriteRegister8(DEFAULT_I2C, PCA9685_Data.address, 0x00, mode1) != NO_ERROR)
  {
    return IO_ERROR;
  }
  
  for (i = 0; i < 0x500; i++) {}
  
  return NO_ERROR;
}


result_t PCA9685_SetPWM(uint8_t index, float delay, float dutyCycle)
{
  uint8_t buff[5];
  
  uint16_t on = (uint16_t)(4095 * delay);
  uint16_t off = (uint16_t)(4095 * dutyCycle);

  buff[0] = PCA9686_LED_START + index*4; /* register id */
  buff[1] = on;
  buff[2] = on >> 8;
  buff[3] = off;
  buff[4] = off >> 8;
  
  static I2C_XFER_T xfer;
  xfer.slaveAddr = PCA9685_Data.address;
  xfer.txBuff = buff;
  xfer.txSz = sizeof(buff);
  
  Chip_I2C_MasterTransfer(DEFAULT_I2C, &xfer);
  
  if(xfer.status != I2C_STATUS_DONE)
  {
    return IO_ERROR;
  }

  return NO_ERROR;
}

result_t PCA9685_Deinit(void)
{
  return NO_ERROR;
}

version_t PCA9685_Version(void)
{
  version_t v = {0, 0, 0};
  return v;
}

result_t PCA9685_SetAddress(uint8_t address)
{
  PCA9685_Data.address = address;
  return NO_ERROR;
}

/* 
 * Call PCA9685_Idle from outside.
 * Uncomment the function call in the macro in header file!
 */
void PCA9685_IdleCall(void)
{
  
}
