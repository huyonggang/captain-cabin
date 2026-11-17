#include <stdint.h>
#include <stdio.h>
#include "debug_assert.h"

void assertFail(char *exp, char *file, int line)
{
	printf("Assert failed %s:%d\n", file, line);
	while (1)
	{
	}
}
