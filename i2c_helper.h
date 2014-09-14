#ifndef _I2C_HELPER__H
#define _I2C_HELPER__H

#include "chip.h"

#define DEFAULT_I2C          I2C0

#define I2C_TEMPSENS_BUS     DEFAULT_I2C

#define SPEED_100KHZ         100000
#define SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    SPEED_100KHZ
#define I2C_FASTPLUS_BIT     0

#define I2C_IRQ_HANDLER(I2C) void I2C_IRQHandler(void) { i2c_state_handling(I2C); }

void Init_I2C_PinMux(void);
void i2c_state_handling(I2C_ID_T id);
void i2c_app_init(I2C_ID_T id, int speed);
int i2c_read16(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint16_t * buff);

#endif