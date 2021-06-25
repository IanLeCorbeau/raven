/* See LICENSE file for copyright and license details. */
#include <err.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "raven.h"

void *
xcalloc(size_t no, size_t siz)
{
	void	*p;

	if (siz == 0 || no == 0)
		errx(1, "xcalloc: zero size");
	if (SIZE_MAX / no < siz)
		errx(1, "xcalloc: no * siz > SIZE_MAX");
	if ((p = calloc(no, siz)) == NULL)
		err(1, "calloc");

	return p;
}

void
die(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(1);
}
