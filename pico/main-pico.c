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
#include "tinyseq.h"

#ifdef USE_STDIO
#include <stdio.h>
#endif //USE_STDIO
#ifdef USE_XPRINTF
#include "xprintf.h"
#endif //USE_XPRINTF

//
// UART or USB-CDC ?
//
#define USE_CDC
//#define USE_UART

#include "pico/stdlib.h"

extern int zmain(int argc, char **argv);
//static void do_timer(void);

//
// machine dependent uart console functions
//
#ifdef USE_UART
#include "pico/stdio_uart.h"
#include "hardware/uart.h"
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
#endif //USE_UART



#ifdef USE_CDC
#include "class/cdc/cdc_device.h"

static void sleep(void)
{
  sleep_us(100);    // 100us wait
}

void con_init(void)
{
  char dummy;
  stdio_init_all();
  // flush any previous gurbage input data
  while(tud_cdc_available() > 0)
    tud_cdc_read(&dummy, 1);
  // some wait for TinyUSB CDC module to startup
  // so far 1sec seems to be enough.
  // If we check tud_cdd_write failure to write, this 1sec
  // waiting might not be needed.
  sleep_ms(1000);
}

int _mon_getc(void)
{
  char c;
  while (tud_cdc_available() == 0) {
    if (get_statusflag()) {
      do_ladder();
      clear_statusflag();
    }
    sleep_ms(2);
  }
  tud_cdc_read(&c, 1);
  return c;
}

void _mon_putc(int c)
{
  char dummy = (char)c;
  while (tud_cdc_write(&dummy, 1) != 1)
    ;
  // tud_cdc_write sometimes fails to write (even) one byte.
  // so return value check is needed.
  tud_cdc_write_flush();
}

void _mon_putc2(int c)
{
  if (c == '\n')
    _mon_putc('\r');
  _mon_putc(c);
}

#endif //USE_CDC

int zf_getline(char *buf, int siz)
{
  zf_cell cell;
  zf_uservar_get(ZF_USERVAR_NOECHO, &cell);
  int noecho = cell;
  xgets(buf, siz, noecho);
  return strlen(buf);
}

//
// GPIO initialize
//
void io_init(void)
{
  gpio_init_mask(0xffff);
  for (int i = 8; i < 16; ++i) {
    gpio_pull_up(i);
  }
  gpio_clr_mask(0xff00);  // GP8-15 cleared before they are activated
  gpio_set_dir_masked(0xffff, 0x00ff);  // GP0-7, output, GP8-15: input
}

//
// bit array to/from gpio, machine dependent, defined in each
// platform.
//


void put_outbits(const uint8_t *bits)
{
  // Y008-015 bit24-32 -> GP0-GP7
  uint32_t outport;
  outport = bits[3];
  gpio_put_masked(0xff, outport);
}

void get_inbits(uint8_t *bits)
{
  // GP8-15 bit8-15 --> X008-015
  bits[1] = ((~gpio_get_all())>>8);
}

//
// timer function
//
#define TIMER_PERIOD 100  // 100ms

static uint32_t seq_tick = TIMER_PERIOD;
static uint32_t seq_clock = 0;

uint32_t get_seq_clock(void)
{
  return seq_clock;
}

static bool repeating_timer_callback(struct repeating_timer *t)
{
  if (--seq_tick <= 0) {
    do_timer();
    seq_tick = TIMER_PERIOD;
  }
  seq_clock++;
  return true;
}

//#define TEST_XPRINTF
#ifdef TEST_XPRINTF
void test_xprintf(void)
{
  xprintf("%d\n", 1234);			//"1234"
  xprintf("%6d,%3d%%\n", -200, 5);	//"  -200,  5%"
  xprintf("%-6u\n", 100);			//"100   "
  xprintf("%ld\n", 12345678);		//"12345678"
  //xprintf("%llu", 0x100000000);	//"4294967296"	<XF_USE_LLI>
  //xprintf("%lld", -1LL);			//"-1"			<XF_USE_LLI>
  xprintf("%04x\n", 0xA3);			//"00a3"
  xprintf("%08lX\n", 0x123ABC);		//"00123ABC"
  xprintf("%016b\n", 0x550F);		//"0101010100001111"
  xprintf("%*d\n", 6, 100);			//"   100"
  xprintf("%s\n", "String");		//"String"
  xprintf("%5s\n", "abc");			//"  abc"
  xprintf("%-5s\n", "abc");			//"abc  "
  xprintf("%-5s\n", "abcdefg");		//"abcdefg"
  xprintf("%-5.5s\n", "abcdefg");	//"abcde"
  xprintf("%-.5s\n", "abcdefg");	//"abcde"
  xprintf("%-5.5s\n", "abc");		//"abc  "
  xprintf("%c\n", 'a');				//"a"
  //xprintf("%12f", 10.0);			"   10.000000"	<XF_USE_FP>
  //xprintf("%.4E", 123.45678);		"1.2346E+02"	<XF_USE_FP>
}
#endif //XPRINTF_TEST

#if 1
char buf[40];

int main(int argc, char **argv)
{
  con_init();
	xdev_out(_mon_putc);
  xdev_in(_mon_getc);

  io_init();

  //
  // add TinySeq syscalls
  //
  init_tinyseq();

  // alarm
  struct repeating_timer timer;
  add_repeating_timer_us(-1000, repeating_timer_callback, NULL, &timer);

#ifdef TEST_XPRINTF
  test_xprintf();
#endif //XPRINTF_TEST


  zf_main(argc, argv);
  xprintf("end of zf_main\n");
  while (1);
  return 0;
}
#endif

#ifdef TEST_BUILDENVIRONMENT
int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
#endif
}
#endif //TEST_BUILDENVIRONMENT

#ifdef TEST_CONSOLE
int main(){
  int c;
  con_init();
  xprintf("hello, world!\n");
  while (1) {
    while ((c = _mon_getc()) == -1);
    _mon_putc(c);
  }
  return 0;
}
#endif //TEST_CONSOLE
