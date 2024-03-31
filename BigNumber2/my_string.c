#include <stdbool.h>
#include "my_string.h"
#include "BigNumber.h"
#include <stdio.h>
#include <stdbool.h>

bool IsIntString(char* str_)
{
	if (str_[0] == '-')
		str_++;

	while (*str_)
	{
		if (*str_ < '0' || *str_ > '9')
			return false;

		str_++;
	}

	return true;
}