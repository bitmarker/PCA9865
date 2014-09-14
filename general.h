/*
 * @brief  General file for inclusion in every file
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
 
#ifndef __GENERAL_H_
#define __GENERAL_H_

#include <stdio.h>
#include <stdint.h>

#if !defined(__CHIP_H_)
	
#endif

typedef enum
{
	NO_ERROR = 0,
	UNKNOWN_ERROR,
	BAD_PARAMETER,
	BAD_INDEX,
        IO_ERROR
} result_t;

typedef struct 
{
	char major;
	char minor;
	uint16_t build;
} version_t;

#endif /* __GENERAL_H_ */
