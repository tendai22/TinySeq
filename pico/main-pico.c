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

//
// UART or USB-CDC ?
//
#define USE_CDC
//#define USE_UART

#include "pico/stdlib.h"

extern int zmain(int argc, char **argv);

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
  while (tud_cdc_available() == 0)
    ;
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
  xgets(buf, siz);
  return strlen(buf);
}

//
// PLC module
//
#define NUM_INPORT 32
#define NUM_OUTPORT 32
#define NUM_COILPORT 32

//
// bit value holding IN/OUT port
//
// In zFlash functions, or tinyseq system calls, inport/outport/coilport are changed.
// In the next do_timer function invokation, these changes to get effect.
int32_t inport;
int32_t outport;
int32_t coilport;

// current(previous) port bit holders
// In 'do_timer' function, if either of inport, outport, coilport is different to
// its corrspoinding 'cur_' value, actual output pins are switched.
int32_t cur_inport;
int32_t cur_outport;
int32_t cur_coilport;

//
// rest timer count for COIL, which counts remaining count number for fire
// (ON-Delay or OFF-Delay), actially toggle (EX-OR) its value.
//
int16_t rest_count[NUM_COILPORT];

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
// read inport pins
//
int32_t get_inport(void)
{
  return (~gpio_get_all()) & 0xff00; // GP8-15 as X008-015
}

int32_t get_coilport(void)
{
  return (cur_coilport) & 0xff00; // GP8-15 as X008-015
}

void set_outport_mask(int32_t mask)
{
  outport |= mask;
}

void clr_outport_mask(int32_t mask)
{
  outport &= ~mask;
}

void set_coilport_mask(int32_t mask)
{
  coilport |= mask;
}

void clr_coilport_mask(int32_t mask)
{
  coilport &= ~mask;
}

//
// write to output pins
//

void put_outport(int32_t outdata)
{
  outdata /= 256;
  outdata &= 0xff;
  gpio_put_masked(0xff, outdata);
}

int32_t do_ladder(void)
{
  // here, a ladder cycle is executed
  // In the ladder cycle, it refers 'inport' and and 'coilport' 
  // and modifies 'outport' and 'coilport'.

  //
  // X008,9,10 -> Y12,13,14
  //
#if 0
  inport <<= 4;
  inport &= 0x7000;    // bit8,9,10
  outport &= ~0x7000;    // clear bit 8,9,10
  outport |= inport;
#endif
  // after outport and coilport revises
  if (cur_inport != inport)
    xprintf("in: %08X\n", inport);
  if (cur_coilport != coilport)
    xprintf("coil: %08X\n", coilport);
  return outport;
}

//
// timer function
//
void do_timer(void)
{
  int32_t mask = 1;
  // activate ON-Delay/OFF-Delay if counter becomes zero
  //coilport = cur_coilport;
  for (int i = 0; i < NUM_COILPORT; ++i, mask<<=1) {
    if (rest_count[i] > 0) {
      xprintf("coil[%d] %d\n", i, rest_count[i]);
      if (--rest_count[i] == 0) {
        // toggle coil value
        coilport ^= mask;
      }
    }
  }
  // examine inport
  inport = get_inport();
  // if any changes occur, do 'ladder' function
  if (cur_coilport != coilport || cur_inport != inport) {
    cur_outport = do_ladder();
    put_outport(cur_outport);
  } else if (cur_outport != outport) {
    put_outport(outport);
    cur_outport = outport;
  }
  cur_coilport = coilport;
  cur_inport = inport;
}

#define _X 65536
const uint32_t _ma[32] = {
  1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 4096*2, 4096*4, 4096*8,
  _X, 2*_X, 4*_X, 8*_X, 16*_X, 32*_X, 64*_X, 128*_X, 256*_X, 512*_X, 1024*_X, 2048*_X, 
  4096*_X, 4096*2*_X, 4096*4*_X, 
};

//
// timer function
//
static bool repeating_timer_callback(struct repeating_timer *t)
{
  do_timer();
  return true;
}

/**
 * primitives
 * L
 * --
 * Xnnn.a ... val nnn 1001 sys --> val' // refer Xnnn.a (inport) contact
 * Xnnn.b ... val nnn 1002 sys --> val' // refer Xnnn.b (inport) contact(negate switch)
 * Mnnn.a ... val nnn 1003 sys --> val' // refer Mnnn.a (internal) contact
 * Mnnn.b ... val nnn 1004 sys --> val' // refer Mnnn.b (internal) contact
 * Ynnn ... val nnn 1005 sys --> val    // set Ynnn(outport) coil
 * Mnnn ... val nnn 1006 sys --> val    // set Mnnn(internal) coil
 * Nnnn ... val delay nnn 1007 sys --> val    // set ON-Delay coil
 * Fnnn ... val delay nnn 1008 sys --> val    // set OFF-Delay coil
 * 
 */ 

//
// custom syscalls
//
int tinyseq_custom_syscalls(zf_syscall_id id, const char *input)
{
  if (id < 1000 || id >= 1100) {
    return -1;
  }
  int port, val;
  int period;
  switch((int)id) {
  case 1000:  // begin_cycle
    xprintf("not supported\n");
    break;
  case 1001:  // val n Xnnn.a --> val'
  case 1002:  // val n Xnnn.b --> val'
              // refer n'th bit of inport and AND-OP with val,
              // result pushed as val'
    port = (int)zf_pop();
    val = (int)zf_pop();
    if (val) {
      val = (get_inport() & (1<<port) ? 1 : 0);
      if ((int)id == 1002)
        val = val ? 0 : 1;
      zf_push(val);
    }
    //xprintf("inport\n");
    break;
  case 1003:  // val n Mnnn.a --> val'
  case 1004:  // val n Mnnn.b --> val'
    port = (int)zf_pop();
    val = (int)zf_pop();
    if (val) {
      val = (get_coilport() & (1<<port) ? 1 : 0);
      if ((int)id == 1004)
        val = val ? 0 : 1;
      zf_push(val);
    }
    break;
  case 1005:  // val n Ynnn --> val'
              // sets val to n'th bit of outport and
              // pushes the same value as val.
    port = (int)zf_pop();
    val = (int)zf_pop();
    if (val) {  // set Ynn bit
      set_outport_mask((1<<port));
    } else {
      clr_outport_mask((1<<port));
    }
    //xprintf("outport\n");
    break;
  case 1006:  // val n Mnnn --> val'
              // sets val to n'th bit of coilport and
              // pushes the same value as val.
    port = (int)zf_pop();
    val = (int)zf_pop();
    if (val) {  // set Ynn bit
      set_coilport_mask((1<<port));
    } else {
      clr_coilport_mask((1<<port));
    }
    //xprintf("outport\n");
    break;
  case 1007:  // OFF-DELAY Timer
  case 1008:  // ON-DELAY Timer
              // val period n Tnnn -> val'
              // set ON-Delay timer
    port = (int)zf_pop();
    period = (int)zf_pop();
    val = (int)zf_pop();
    if (port < 0 || NUM_COILPORT <= port) {
      xprintf("bad period %d\n", port);
      return ZF_INPUT_INTERPRET;
    }
    if (rest_count[port] > 0) { // ignore this timer
      return ZF_INPUT_INTERPRET;
    }
    // set timer, if value > 0
    if (val == 0) {
      return ZF_INPUT_INTERPRET;  // do nothing if val is zero
    }
    rest_count[port] = period;
    if ((int)id == 1007) {  // ON-DELAY, initial value should be zero
      clr_coilport_mask(1<<port);
    }
    if ((int)id == 1008) {  // OFF-DELAY, set one
      set_coilport_mask(1<<port);
    }
    break;
  default:
    return -1;
  }
  return ZF_INPUT_INTERPRET;
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
  zf_add_syscall(tinyseq_custom_syscalls);

  // alarm
  struct repeating_timer timer;
  add_repeating_timer_ms(-100, repeating_timer_callback, NULL, &timer);

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
