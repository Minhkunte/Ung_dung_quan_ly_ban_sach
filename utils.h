#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void pause()
{
	char c;
	fflush(stdin);
	scanf("%c",&c);
	fflush(stdin);
}

void print_gachngang(int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		printf("-");
	}
}

#endif
