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

#ifndef __PCA9685_H_
#define __PCA9685_H_

#include "general.h"

#define PCA9685_CMD_SWRST       0x06
#define PCA9686_LED_START       0x06

#define PCA9685_Idle() /* PCA9685_IdleCall() */

/* 
 * Call PCA9685_Idle from outside.
 * Uncomment the function call in the macro in header file!
 */
void PCA9685_IdleCall(void);

result_t PCA9685_Init(void);

result_t PCA9685_Deinit(void);

version_t PCA9685_Version(void);

result_t PCA9685_SetAddress(uint8_t address);

result_t PCA9685_SetPWM(uint8_t index, float delay, float dutyCycle);

#endif /* PCA9685 */
