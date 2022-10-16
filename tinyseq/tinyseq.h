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

#ifndef __TINYSEQ_H
#define __TINYSEQ_H
#include <inttypes.h>
#include "tinyseq.h"

//
// constants
//
#define NUM_BITS    66
#define BITS_SIZE   ((NUM_BITS + 7)/8)

#define START_COIL 48
#define NUM_COIL 16

//
// bit array manipulation, defined in tinyseq.c
//
extern int get_prev_bit(int n);
extern void set_prev_bit(int n);
extern void clr_prev_bit(int n);
extern void toggle_prev_bit(int n);
extern int get_cur_bit(int n);
extern void set_cur_bit(int n);
extern void clr_cur_bit(int n);
extern void toggle_cur_bit(int n);
// compare/copy to bits to prev_bits
extern int compare_bits(int doprint_flag);
extern void copy_bits(void);
//
// bit array to/from gpio, machine dependent, defined in each
// platform.
//
extern void put_outbits(const uint8_t *bits);
extern void get_inbits(uint8_t *bits);

//
// do_ladder ... 
//
void do_timer(void);
void do_ladder(void);

//
// initialization
//
void init_tinyseq(void);

//
// status flag ... set 1 in do_timer so that zforth system can invoke do_ladder
//
void set_statusflag(int val);
void clear_statusflag(void);
int get_statusflag(void);


#endif //__TINYSEQ_H
