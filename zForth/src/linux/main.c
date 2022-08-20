
//#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "zforth.h"
#include "xprintf.h"

/*
 *
 */

int _mon_getc(void)
{
	char c;
	int r = read(0, &c, 1); 
	return r == 1 ? c : -1;
}

void _mon_putc(int c)
{
	char buf[1];
	buf[0] = (char)c;
	write(1, buf, 1);
}

/*
 * Main
 */

int main(int argc, char **argv)
{
	zmain (0, NULL);
	return 0;
}


/*
 * End
 */

