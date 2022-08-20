//
//
//

#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>

#include "zforth.h"

#ifdef USE_STDIO
#include <stdio.h>
#endif //USE_STDIO
#ifdef USE_XPRINTF
#include "xprintf.h"
#endif //USE_XPRINTF

//
// extern declaration
//
extern const char zf_src_core_file[];
extern int _mon_getc(void);
extern void _mon_putc(int c);

//
// xprintf support functions
//
#ifdef USE_XPRINTF
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
#endif // USE_XPRINTF

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

/*
 * Load given forth file
 */

void include(const char *fname)
{
#if 0
	char buf[256];

	FILE *f = fopen(fname, "rb");
	int line = 1;
	if(f) {
		while(fgets(buf, sizeof(buf), f)) {
			do_eval(fname, line++, buf);
		}
		fclose(f);
	} else {
		yprintf("error opening file '%s': %s\n", fname, strerror(errno));
	}
#endif
}

/*
 * Save dictionary
 */

static void save(const char *fname)
{
#if 0
	size_t len;
	void *p = zf_dump(&len);
	FILE *f = fopen(fname, "wb");
	if(f) {
		fwrite(p, 1, len, f);
		fclose(f);
	}
#endif
}

/*
 * Load dictionary
 */

static void load(const char *fname)
{
#if 0
	size_t len;
	void *p = zf_dump(&len);
	FILE *f = fopen(fname, "rb");
	if(f) {
		fread(p, 1, len, f);
		fclose(f);
	} else {
		perror("read");
	}
#endif
}

//
// include from an embedded character array (which holds a source code)
//

void include_str(const char *fname, const char *str)
{
	char buf[256];
	const char *src = str;
	char *dest = buf;
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
		dest = buf;
		yprintf ("%s:%d:%s\r\n", fname, line, buf);
		do_eval(fname, line++, buf);
	}
}

/*
 * Sys callback function
 */

zf_input_state zf_host_sys(zf_syscall_id id, const char *input)
{
	switch((int)id) {


		/* The core system callbacks */

		case ZF_SYSCALL_EMIT:
			xputc((char)zf_pop());
#ifdef USE_STDIO
			fflush(stdout);
#endif //USE_STDIO
			break;

		case ZF_SYSCALL_PRINT:
			xprintf(ZF_CELL_FMT " ", zf_pop());
			break;

		case ZF_SYSCALL_TELL: {
			zf_cell len = zf_pop();
			void *buf = (uint8_t *)zf_dump(NULL) + (int)zf_pop();
#ifdef USE_STDIO
			(void)fwrite(buf, 1, len, stdout);
			fflush(stdout);
#endif //USE_STDIO
#ifdef USE_XPRINTF
			while (len-- > 0) {
				xputc(*(char *)buf++);
			}
#endif //USE_XPRINTF
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

		case ZF_SYSCALL_USER + 2:
			if(input == NULL) {
				return ZF_INPUT_PASS_WORD;
			}
			include(input);
			break;
		
		case ZF_SYSCALL_USER + 3:
			save("zforth.save");
			break;

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
#ifdef USE_STDIO
	int r = sscanf(buf, "%f%n", &v, &n);
#endif //USE_STDIO
#ifdef USE_XPRINTF
	const char *p = buf;
	int r = xatoi(&p, &v);
	n = p - buf;
#endif //USE_XPRINTF
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

//
//
//

int zf_fgets(char *buf, size_t len/*, FILE *fp*/)
{
    int i, c;
    for (i = 0; i < len ; ) {
        while ((c = _mon_getc()) == -1)
            ;
        if (i >= len - 1 || c == '\r' || c == '\n') {
            buf[i] = '\0';
            _mon_putc('\r');
            _mon_putc('\n');
            break;
        }
        buf[i++] = c;
        _mon_putc(c);
    }
    return i;
}

/*
 * Main
 */

int zmain(int argc, char **argv)
{
	int i;
	//int c;
	int trace = 0;
	int line = 0;
	const char *fname_load = NULL;

	/* Parse command line options */
#if 0
	while((c = getopt(argc, argv, "hl:t")) != -1) {
		switch(c) {
			case 't':
				trace = 1;
				break;
			case 'l':
				fname_load = optarg;
				break;
			case 'h':
				usage();
				exit(0);
		}
	}
	
	argc -= optind;
	argv += optind;
#endif

	/* Initialize zforth */

	zf_init(trace);


	/* Load dict from disk if requested, otherwise bootstrap fort
	 * dictionary */

	if(fname_load) {
		load(fname_load);
	} else {
		zf_bootstrap();
	}


	/* Include files from command line */

	for(i=0; i<argc; i++) {
		include(argv[i]);
	}

	include_str("core.zf", &zf_src_core_file[0]);


	/* Interactive interpreter: read a line using readline library,
	 * and pass to zf_eval() for evaluation*/

#ifdef USE_READLINE

	read_history(".zforth.hist");

	for(;;) {

		char *buf = readline("");
		if(buf == NULL) break;

		if(strlen(buf) > 0) {

			do_eval("stdin", ++line, buf);
			printf("\n");

			add_history(buf);
			write_history(".zforth.hist");

		}

		free(buf);
	}
#else
	for(;;) {
		char buf[256];
		if(zf_fgets(buf, sizeof(buf)/*, stdin*/)) {
            xprintf("<%s>", buf);
			do_eval("conin", ++line, buf);
			xprintf("\r\n");
		} else {
			break;
		}
	}
#endif

	return 0;
}


/*
 * End
 */
