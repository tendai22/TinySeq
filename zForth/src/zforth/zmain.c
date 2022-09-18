//
//
//

#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>

#include "zforth.h"

//#define USE_XPRINTF

#include "xprintf.h"

//
// extern declaration
//
extern const char zf_src_core_file[];

//
// getline, which we need to define in each platform
//
// In UNIX/Linux environments, we define getline function as calling gets_s
// in main.c.  In these environemnts, line edit functionality is provided in tty driver.
// So we depend on it, and need not implement any explicit line edit functinlality 
// In most embedded environments including pico, pic32mx, ..., no line edit functionality
// is provided in their library, so we write getline function in their main.c 
// using 'xgets' function in 'xprintf' package.
//
// getline returns number of characters in the buffer, 'buf'.
//
extern int zf_getline (char *buf, int length);

//
// xprintf support functions
//
//void (*xfunc_output)(int) = _mon_putc;


void vyprintf(const char *fmt, va_list arp)
{
	xvfprintf(_mon_putc, fmt, arp);
}

void yprintf(const char *fmt, ...)
{
	va_list arp;
	va_start(arp, fmt);
	xvfprintf(_mon_putc, fmt, arp);
	va_end(arp);
}

/*
 * Evaluate buffer with code, check return value and report errors
 */

zf_result do_eval(const char *src, int line, const char *buf)
{
	const char *msg = NULL;

	zf_result rv = zf_eval(buf);

	switch(rv)
	{
		case ZF_OK: break;
		case ZF_ABORT_INTERNAL_ERROR: msg = "internal error"; break;
		case ZF_ABORT_OUTSIDE_MEM: msg = "outside memory"; break;
		case ZF_ABORT_DSTACK_OVERRUN: msg = "dstack overrun"; break;
		case ZF_ABORT_DSTACK_UNDERRUN: msg = "dstack underrun"; break;
		case ZF_ABORT_RSTACK_OVERRUN: msg = "rstack overrun"; break;
		case ZF_ABORT_RSTACK_UNDERRUN: msg = "rstack underrun"; break;
		case ZF_ABORT_NOT_A_WORD: msg = "not a word"; break;
		case ZF_ABORT_COMPILE_ONLY_WORD: msg = "compile-only word"; break;
		case ZF_ABORT_INVALID_SIZE: msg = "invalid size"; break;
		case ZF_ABORT_DIVISION_BY_ZERO: msg = "division by zero"; break;
		default: msg = "unknown error";
	}

	if(msg) {
		yprintf("\033[31m");
		if(src) yprintf("%s:%d: ", src, line);
		yprintf("%s\033[0m\n", msg);
	}

	return rv;
}

//
// include from an embedded character array (which holds a source code)
//
static char _buf[256];

void include_str(const char *fname, const char *str)
{
	const char *src = str;
	char *dest = _buf;
	int c, line = 1;
	while ((c = *src++) != 0) {
		if (c == '\r')
			continue; 	// ignore carridge return
		if (c != '\n') {
			*dest++ = c;
			continue;
		}
		// end of line
		*dest = '\0';
		dest = _buf;
		//yprintf ("%s:%ld:%s\r\n", fname, line, _buf);
		do_eval(fname, line++, _buf);
	}
}

/*
 * Sys callback function
 */
static int (*custom_func)(zf_syscall_id, const char *) = NULL;

void zf_add_syscall(int (*func)(zf_syscall_id, const char *))
{
	custom_func = func;
}


zf_input_state zf_host_sys(zf_syscall_id id, const char *input)
{
	int res;
	if (custom_func && (res = (*custom_func)(id, input)) != -1) {
		return res;
	}
	switch((int)id) {

		/* The core system callbacks */

		case ZF_SYSCALL_EMIT:
			xputc((char)zf_pop());
			break;

		case ZF_SYSCALL_PRINT:
			xprintf(ZF_CELL_FMT " ", zf_pop());
			break;

		case ZF_SYSCALL_TELL: {
				zf_cell len = zf_pop();
				void *buf = (uint8_t *)zf_dump(NULL) + (int)zf_pop();
				for (char *p = (char *)buf; len-- > 0; ) {
					xputc(*p++);
				}
		    }
			break;
		/* Application specific callbacks */

		case ZF_SYSCALL_USER + 0:
			xprintf("\r\n");
			exit(0);
			break;

		case ZF_SYSCALL_USER + 1:
			//zf_push(sin(zf_pop()));
			break;
#ifdef ZF_USE_FILE
		case ZF_SYSCALL_USER + 2:
			if(input == NULL) {
				return ZF_INPUT_PASS_WORD;
			}
			include(input);
			break;
		
		case ZF_SYSCALL_USER + 3:
			save("zforth.save");
			break;
#endif //ZF_USE_FILE
		default:
			xprintf("unhandled syscall %d\r\n", id);
			break;
	}

	return ZF_INPUT_INTERPRET;
}


/*
 * Tracing output
 */

void zf_host_trace(const char *fmt, va_list va)
{
	yprintf("\033[1;30m");
	vyprintf(fmt, va);
	yprintf("\033[0m");
}


/*
 * Parse number
 */

zf_cell zf_host_parse_num(const char *buf)
{
	zf_cell v;
	int n = 0;
	const char *p = buf;
	int r = xatoi(&p, &v);
	n = p - buf;
	if(r == 0 || buf[n] != '\0') {
		zf_abort(ZF_ABORT_NOT_A_WORD);
	}
	return v;
}

void usage(void)
{
	yprintf( 
		"usage: zfort [options] [src ...]\r\n"
		"\r\n"
		"Options:\r\n"
		"   -h         show help\r\n"
		"   -t         enable tracing\r\n"
		"   -l FILE    load dictionary from FILE\r\n"
	);
}


/*
 * Main
 */
static char linebuf[80];

int zf_main(int argc, char **argv)
{
//	int i;
	int trace = 0;
	int line = 0;

	/* Initialize zforth */

	zf_init(trace);


	/* Load dict from disk if requested, otherwise bootstrap fort
	 * dictionary */

	zf_bootstrap();

	/* load core.zf array
	 */

	include_str("core.zf", &zf_src_core_file[0]);

	/*
	 * interactive interpreter
	 */
	while (1) {
		if(zf_getline(linebuf, sizeof(linebuf)) >= 0) {
			do_eval("conin", ++line, linebuf);
		} else {
			break;
		}
	}

	return 0;
}


/*
 * End
 */
