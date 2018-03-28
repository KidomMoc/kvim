#include "kvim.h"

int getNumLen (int n)
{
	int l = 1, pow = 1;
	for ( ; n / (pow *= 10); ++l)
		;
	return l;
}

char* convertNumToStr (int n, int *len)
{
	*len = getNumLen (n);
	int pow = 1;
	for (int i = 0; i < *len; ++i)
		pow *= 10;
	char *s = malloc (*len);
	for (int i = 0; i < *len; ++i, n %= pow)
		s[i] = n / (pow /= 10) + 48;
	return s;
}

int convertStrToNum (int* s, int len)
{
	int a = 0;
	for (int i = 0; i < len; ++i)
		a = a * 10 + s[i] - 48;
	return a > 0 ? a : 1;
}

int setStatus (const char *buf, int len)
{
	if (kvim.status)
	{
		free (kvim.status);
		kvim.stlen = 0;
	}

	if (len < kvim.cols)
	{
		kvim.status = malloc (len);
		memcpy (kvim.status, buf, len);
		kvim.stlen = len;
	}
	else
	{
		kvim.status = malloc (kvim.cols - 1);
		kvim.status[0] = '<';
		memcpy (kvim.status + 1, &buf[len - kvim.cols + 1],
			kvim.cols - 2);
		kvim.stlen = kvim.cols - 1;
	}
	return 0;
}

int appendInputBuf (int c)
{
	ib.inputBuf[ib.len] = c;
	++ib.len;
	return 0;
}

int getIbNum (void)
{
	int n = convertStrToNum (ib.inputBuf, ib.len);
	ib.len = 0;
	return n;
}

/* compareStr: compare <str1> and <str2>
 * return 1 -> equal, 0 -> not equal
 */
int compareStr (char *str1, char *str2, int len)
{
	for ( ; len > 0; --len, ++str1, ++str2)
		if (*str1 != *str2)
			return 0;
	return 1;
}
