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

#ifndef __I2C_H_
#define __I2C_H_

#include "general.h"
#include "chip.h"

#define DEFAULT_I2C          I2C0

#define I2C_TEMPSENS_BUS     DEFAULT_I2C

#define SPEED_100KHZ         100000
#define SPEED_400KHZ         400000
#define I2C_DEFAULT_SPEED    SPEED_100KHZ
#define I2C_FASTPLUS_BIT     0

#define I2C_Idle() /* I2C_IdleCall() */

/* 
 * Call I2C_Idle from outside.
 * Uncomment the function call in the macro in header file!
 */
void I2C_IdleCall(void);

result_t I2C_Init(void);

result_t I2C_Deinit(void);

version_t I2C_Version(void);

result_t I2C_Read16(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint16_t * buff);

result_t I2C_Write8(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd);

result_t I2C_WriteRegister8(I2C_ID_T id, uint8_t slaveAddr, uint8_t registerId, uint8_t data);

#endif /* I2C */
