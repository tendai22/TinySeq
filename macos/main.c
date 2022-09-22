
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

#include <stdio.h>

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
 * getline function, using gets_s
*/

int zf_getline (char *buf, int length)
{

	fgets(buf, length, stdin);
	int len = strlen(buf);
	if (len > 1 && buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	int res = feof(stdin) ? -1 : (ferror(stdin) ? -1 : (int)strlen(buf));
	return res;
}

/*
 * Main
 */

int main(int argc, char **argv)
{
	// xprintf initialize
	xdev_out(_mon_putc);
  	xdev_in(_mon_getc);

	// all-in-one zforth interpreter
	zf_main (0, NULL);
	
	// end-of-zf_main marking
	yprintf("end of zf_main\n");
	return 0;
}


/*
 * End
 */

