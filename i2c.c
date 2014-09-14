/*
 * @brief  I2C
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

#include "i2c.h"

/*****************************************************************************
* Private types/enumerations/variables
****************************************************************************/

static struct
{
  int dummy;
} I2C_Data;

/*****************************************************************************
* Public types/enumerations/variables
****************************************************************************/

/*****************************************************************************
* Private functions
****************************************************************************/

static void I2C_StateHandling(I2C_ID_T id)
{
  if (Chip_I2C_IsMasterActive(id)) {
    Chip_I2C_MasterStateHandler(id);
  }
  else {
    Chip_I2C_SlaveStateHandler(id);
  }
}

void I2C_IRQHandler(void)
{
  I2C_StateHandling(DEFAULT_I2C);
}

/*****************************************************************************
* Public functions
****************************************************************************/

result_t I2C_Init(void)
{
  Chip_SYSCTL_PeriphReset(RESET_I2C0);
  
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4, IOCON_FUNC1 | I2C_FASTPLUS_BIT);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5, IOCON_FUNC1 | I2C_FASTPLUS_BIT);

  // Initialize I2C
  Chip_I2C_Init(DEFAULT_I2C);
  Chip_I2C_SetClockRate(DEFAULT_I2C, I2C_DEFAULT_SPEED);

  // Set default mode to interrupt
  Chip_I2C_SetMasterEventHandler(DEFAULT_I2C, Chip_I2C_EventHandler);
  
  NVIC_EnableIRQ(I2C0_IRQn);
  
  return NO_ERROR;
}

result_t I2C_Deinit(void)
{
  return NO_ERROR;
}

version_t I2C_Version(void)
{
  version_t v = {0, 0, 1};
  return v;
}

/* 
 * Call I2C_Idle from outside.
 * Uncomment the function call in the macro in header file!
 */
void I2C_IdleCall(void)
{
  
}

result_t I2C_Write8(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd)
{
  static I2C_XFER_T xfer;
  xfer.slaveAddr = slaveAddr;
  xfer.txBuff = &cmd;
  xfer.txSz = 1;
  
  Chip_I2C_MasterTransfer(id, &xfer);
  
  if(xfer.status != I2C_STATUS_DONE)
  {
    return IO_ERROR;
  }

  return NO_ERROR;
}

result_t I2C_WriteRegister8(I2C_ID_T id, uint8_t slaveAddr, uint8_t registerId, uint8_t data)
{
  uint8_t buff[2];
  
  buff[0] = registerId;
  buff[1] = data;

  static I2C_XFER_T xfer;
  xfer.slaveAddr = slaveAddr;
  xfer.txBuff = buff;
  xfer.txSz = 2;
  
  Chip_I2C_MasterTransfer(id, &xfer);
  
  if(xfer.status != I2C_STATUS_DONE)
  {
    return IO_ERROR;
  }

  return NO_ERROR;
}

result_t I2C_Read16(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint16_t * buff)
{
  uint8_t data[2];

  static I2C_XFER_T xfer;
  xfer.slaveAddr = slaveAddr;
  xfer.txBuff = &cmd;
  xfer.txSz = 1;
  xfer.rxBuff = data;
  xfer.rxSz = 2;
  
  Chip_I2C_MasterTransfer(id, &xfer);
  
  if(xfer.status != I2C_STATUS_DONE)
  {
    return IO_ERROR;
  }
  
  *buff = (data[0] << 8) | (data[1]);
  
  return NO_ERROR;
}