#ifndef zforth_h
#define zforth_h

#include "zfconf.h"

/* Abort reasons */

typedef enum {
	ZF_OK,
	ZF_ABORT_INTERNAL_ERROR,
	ZF_ABORT_OUTSIDE_MEM,
	ZF_ABORT_DSTACK_UNDERRUN,
	ZF_ABORT_DSTACK_OVERRUN,
	ZF_ABORT_RSTACK_UNDERRUN,
	ZF_ABORT_RSTACK_OVERRUN,
	ZF_ABORT_NOT_A_WORD,
	ZF_ABORT_COMPILE_ONLY_WORD,
	ZF_ABORT_INVALID_SIZE,
	ZF_ABORT_DIVISION_BY_ZERO,
	ZF_ABORT_INVALID_USERVAR,
	ZF_ABORT_EXTERNAL
} zf_result;

typedef enum {
	ZF_INPUT_INTERPRET,
	ZF_INPUT_PASS_CHAR,
	ZF_INPUT_PASS_WORD
} zf_input_state;

typedef enum {
	ZF_SYSCALL_EMIT,
	ZF_SYSCALL_PRINT,
	ZF_SYSCALL_TELL,
	ZF_SYSCALL_USER = 2000
	// If we need to use any bigger number than 255,
	// we specify any of 2byte integer here
} zf_syscall_id;

typedef enum {
    ZF_USERVAR_HERE = 0,
    ZF_USERVAR_LATEST,
    ZF_USERVAR_TRACE,
    ZF_USERVAR_COMPILING,
    ZF_USERVAR_POSTPONE,

    ZF_USERVAR_COUNT
} zf_uservar_id;


/* ZForth API functions */


void zf_init(int trace);
void zf_bootstrap(void);
void *zf_dump(size_t *len);
zf_result zf_eval(const char *buf);
void zf_abort(zf_result reason);

void zf_push(zf_cell v);
zf_cell zf_pop(void);
zf_cell zf_pick(zf_addr n);

zf_result zf_uservar_set(zf_uservar_id uv, zf_cell v);
zf_result zf_uservar_get(zf_uservar_id uv, zf_cell *v);

/* add custom_syscalls */
/* func returns 1, if it handles id, otherwise return 0. */
void zf_add_syscall(int (*func)(zf_syscall_id, const char *));

/* Host provides these functions */

zf_input_state zf_host_sys(zf_syscall_id id, const char *last_word);
void zf_host_trace(const char *fmt, va_list va);
zf_cell zf_host_parse_num(const char *buf);

int zf_getline(char *buf, int len);

/* zmain functions */
extern int _mon_getc(void);
extern void _mon_putc(int c);
extern void _mon_putc2(int c);
extern void vyprintf(const char *fmt, va_list arp);
extern void yprintf(const char *fmt, ...);
extern zf_result do_eval(const char *src, int line, const char *buf);
extern int zf_main(int argc, char **argv);


#endif
