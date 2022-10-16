/*
 * Copyright (c) 2022, Norihiro KUMAGAI <tendai22plus@gmail.com>
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

//
// tinyseq ... Sequencer(PLC) modules
//

#include <inttypes.h>
#include <string.h>
#include "zforth.h"
#include "tinyseq.h"
#include "xprintf.h"
//
// definition is expected in main.c (platform dependent)
//
extern uint32_t get_seq_clock();

//
// bit array manipulation
//
static uint8_t prev_bits[BITS_SIZE];
static uint8_t bits[BITS_SIZE];
#define _BIT(array,n) (array[(n)/8]&(1<<(n%8)))
#define SET_BIT(array,n) (array[(n)/8]|=(1<<(n%8)))
#define CLR_BIT(array,n) (array[(n)/8]&=~(1<<(n%8)))
#define TGL_BIT(array,n) (array[(n)/8]^=(1<<(n%8)))

int get_prev_bit(int n) {   return _BIT(prev_bits,n) != 0; }
void set_prev_bit(int n) {  SET_BIT(prev_bits,n); }
void clr_prev_bit(int n) {  CLR_BIT(prev_bits,n); }
void toggle_prev_bit(int n) {  TGL_BIT(prev_bits,n); }
int get_cur_bit(int n) {    return _BIT(bits,n) != 0; }
void set_cur_bit(int n) {   SET_BIT(bits,n); }
void clr_cur_bit(int n) {   CLR_BIT(bits,n); }
void toggle_cur_bit(int n) {   TGL_BIT(bits,n); }

int compare_bits(int doprint_flag)
{
    extern void print_bits(int flag);
    int res = memcmp(bits, prev_bits, BITS_SIZE) != 0;
    
    //doprint_flag = 0;
    if (doprint_flag && res) {
        print_bits(1);
        print_bits(0);
    }
    return res;
}

void copy_bits(void)
{
    memcpy(prev_bits, bits, BITS_SIZE);
}

void print_bits(int flag)
{
    const uint8_t *p = (flag ? prev_bits : bits);
    xprintf("%c ", (flag ? 'p' : 'c'));
    xprintf("%02b ", (p[8]&0x3));
    for (int i = 7; i >= 0; --i) {
        xprintf("%08b ", p[i]);
    }
    xprintf("\n");
}

//
// Relay Definition
//

//
// X000-X015: inbit 0-15
// Y000-Y015: outbit 16-31
// M000-M015: internal relay 32-47
// N000-N008: on-delay 48-55
// F000-F008: off-delay 56-63
//

//
// status_flag:  to tell zForth 'ladder' word to be invoked.
// for every timer activation, and check if any of inport/coilport changes occur,
// if any changes occur, status_flag to be set.
// IN zForth interpreter, its getchar(_mon_get()) function polls this flag
// and when it occurs, it returns with -1 so that its interpreter can call
// a 'laddter' word.
//
static int status_flag = 0;

int get_statusflag(void)
{
    return status_flag;
}

void set_statusflag(int val)
{
    status_flag = val;
}

void clear_statusflag(void)
{
    set_statusflag(0);
}

//
// rest timer count for COIL, which counts remaining count number for fire
// (ON-Delay or OFF-Delay), actially toggle (EX-OR) its value.
//
#define NUM_COIL 16
static uint32_t rest_count[NUM_COIL];

//
// do_timer ... detect status changes in bit array
//
//
void do_timer(void)
{
    // at first save current bits to 'previous'
    //copy_bits();
    // activate ON-Delay/OFF-Delay if counter becomes zero
    //coilport = cur_coilport;
    for (int i = 0; i < NUM_COIL; ++i) {
        if (rest_count[i] > 0) {
            xprintf("coil[%d] %d\n", i, rest_count[i]);
            if (--rest_count[i] == 0) {
                // toggle coil value
                toggle_cur_bit(i + START_COIL); // N/F relays starts from bit48.
            }
        }
    }
    // examine inport
    get_inbits(&bits[0]);
    // check if any changes occur
    if (compare_bits(0)) {
        //xprintf("%ld: changed\n", get_seq_clock());
        xputc('x');
        set_statusflag(1); // activate do_ladder
    }
}

/*
 * do_ladder ... execute 'ladder' word
 */
void do_ladder(void)
{
	int res, count = 3;
	uint32_t start;
	start = get_seq_clock();
    res = ZF_OK;
    //
    // Repeatedly invoke 'ladder' function until no 'bit changes' occur
    //
    //xprintf("begin ladder\n");
    while (count-- > 0 && (compare_bits(1) && res == ZF_OK)) {
        copy_bits();
    	res = zf_eval("ladder ");
    }
    //xprintf("end\n");
    put_outbits(&bits[0]);
	if (res == ZF_OK) {
		//xprintf("%ld -> %ld\n", start, get_seq_clock());
	} else {
		//xprintf("err = %d\n", res);
	}
}

/**
 * Register Map (in 64bit array)
 * 
 * nnn assignment:
 *  0-15:  X000-X015  Input switch
 * 16-31:  Y000-Y015  Output relay and contacts
 * 32-47:  M000-M015  Relay and contacts
 * 48-55:  N000-N007  ON-Delay relay and contacts
 * 56-63:  F000-F007  OFF-Delay relay and contacts
 * 
 * primitives:
 * Xnnn.a, Mnnn.a, Nnnn.a, Fnnn.a
 *   ... val nnn 130 sys --> val' // refer Xnnn.a, nnn = 0 - 15
 * Xnnn.b, Mnnn.b, Nnnn.b, Fnnn.b
 *   ... val nnn 131 sys --> val' // refer Xnnn.b (inport) contact(negate switch)
 * Ynnn, Mnnn
 *   ... val nnn 132 sys --> val    // set nnn(outport) coil, nnn = 0 - 15
 * Nnnn
 *   ... val nnn 133 sys --> val    // set nnn(ON Delay) coil, nnn = 0 - 7
 * Fnnn
 *   ... val nnn 134 sys --> val    // set nnn(OFF Delay) coil, nnn = 0 - 7
 */ 

//
// custom syscalls
//
int tinyseq_custom_syscalls(zf_syscall_id id, const char *input)
{
    int port, val, val1, state;
    int period;
    int off_delay_flag = 1;
    int negate_switch_flag = 1;

    if (id < (ZF_SYSCALL_USER + 1) || id >= (ZF_SYSCALL_USER + 6)) {
        return -1;
    }
    switch((int)id) {
    case ZF_SYSCALL_USER + 1:  // 129: begin_cycle
        xprintf("not supported\n");
        break;
    case ZF_SYSCALL_USER + 2:  // 130: a switch get bit: val n --> val'
        negate_switch_flag = 0;
    case ZF_SYSCALL_USER + 3:  // 131: b switch
              // get bit::n
        port = (int)zf_pop();
        val = (int)zf_pop();
        state = get_cur_bit(port);
        if (negate_switch_flag)
            state = !state;
        state = state && val;
        xprintf("%d %d %d -> %d\n", val, port, ZF_SYSCALL_USER + 2, state);
        zf_push(state);
        //xprintf("inport\n");
        break;
    case ZF_SYSCALL_USER + 4:  // 132: set bit : val n Ynnn --> val'
              // sets val to n'th bit of outport and
              // pushes the same value as val.
        port = (int)zf_pop();
        val = (int)zf_pop();
        xprintf("%d %d %d\n", val, port, ZF_SYSCALL_USER + 3);
        if (val) {  // set Ynn bit
            set_cur_bit(port);
        } else {
            clr_cur_bit(port);
        }
        zf_push(val);
        //xprintf("outport\n");
        break;
    case ZF_SYSCALL_USER + 5:  // 133: ON-DELAY Timer
        off_delay_flag = 0;
        // falling down
    case ZF_SYSCALL_USER + 6:   // 134: OFF-DELAY Timer
        port = (int)zf_pop();
        period = (int)zf_pop();
        val = (int)zf_pop();
        state = (get_cur_bit(port) != 0);
        if (port < START_COIL || port <= (START_COIL + NUM_COIL)) {
            xprintf("bad port %d\n", port);
            zf_push(val);
            return ZF_INPUT_INTERPRET;
        }
        if (off_delay_flag) {
            // OFF Delay Relay
            if (val != 0) {
                // cancel off-delay timer, ON forever
                rest_count[port] = 0;
            } else if (rest_count[port] > 0) {
                // keep its state
            } else if (state != 0) {
                // set contact and start count
                set_cur_bit(port);
                rest_count[port] = period;
            }
        } else {
            // ON Delay Relay
            if (val == 0) {
                // cancel ON Delay timer, OFF forever
                rest_count[port] = 0;
                set_cur_bit(port);
            } else if (rest_count[port] > 0) {
                // keep its state
            } else if (state == 0) {
                // reset contact
                clr_cur_bit(port);
                rest_count[port] = period;
            }
        }
        val = (get_cur_bit(port) != 0);
        zf_push(val);
        break;
    default:
        return -1;
    }
    return ZF_INPUT_INTERPRET;
}

void init_tinyseq(void)
{
    zf_add_syscall(tinyseq_custom_syscalls);
}



