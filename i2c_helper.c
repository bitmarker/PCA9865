#include "i2c_helper.h"

void Init_I2C_PinMux(void)
{
  Chip_SYSCTL_PeriphReset(RESET_I2C0);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4, IOCON_FUNC1 | I2C_FASTPLUS_BIT);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5, IOCON_FUNC1 | I2C_FASTPLUS_BIT);
}

void i2c_state_handling(I2C_ID_T id)
{
  if (Chip_I2C_IsMasterActive(id)) {
    Chip_I2C_MasterStateHandler(id);
  }
  else {
    Chip_I2C_SlaveStateHandler(id);
  }
}

void i2c_app_init(I2C_ID_T id, int speed)
{
  Init_I2C_PinMux();

  // Initialize I2C
  Chip_I2C_Init(id);
  Chip_I2C_SetClockRate(id, speed);

  // Set default mode to interrupt
  Chip_I2C_SetMasterEventHandler(id, Chip_I2C_EventHandler);
  
  NVIC_EnableIRQ(I2C0_IRQn);
}

int i2c_read16(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint16_t * buff)
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
    return 1;
  } 
  
  *buff = (data[0] << 8) | (data[1]);
  
  return 0;
}