/*
 * Copyright (c) 2021, Norihiro KUMAGAI <tendai22plus@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * - Neither the name of the authors nor the names of its contributors may be
 *   used to endorse or promote products derived from this software with out
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUE
 * NTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

//#include "machine.h"

#include <stddef.h>
#include <stdarg.h>
#include <inttypes.h>

#include "zforth.h"

#ifdef USE_STDIO
#include <stdio.h>
#endif //USE_STDIO
#ifdef USE_XPRINTF
#include "xprintf.h"
#endif //USE_XPRINTF

#include "pico/stdlib.h"
#include "pico/stdio_uart.h"
#include "hardware/uart.h"

extern int zmain(int argc, char **argv);

//
// machine dependent console functions
//
#define UART_ID uart_default
#define BAUD_RATE 115200

// We are using pin 0 and 1, but, see the GPIO function select in the 
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 16
#define UART_RX_PIN 17

static void sleep(void)
{
  sleep_us(100);    // 100us wait
}

void con_init(void)
{
  stdio_uart_init_full(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
  while(uart_is_readable(UART_ID))
    uart_getc(UART_ID);
}

int _mon_getc(void)
{
  if (uart_is_readable(UART_ID)) {
    return uart_getc(UART_ID);
  }
  sleep();
  return uart_is_readable(UART_ID) ? uart_getc(UART_ID) : -1;
}

void _mon_putc(int c)
{
  while (!uart_is_writable(UART_ID))
    sleep();
  uart_putc(UART_ID, (char)c);
}


int main(int argc, char **argv)
{
  con_init();
  zmain(argc, argv);
  return 0;
}

void
platform_reset
(void)
{
  // so far, a temporal remedy
  xprintf("platform_reset should be implemented.");
}
