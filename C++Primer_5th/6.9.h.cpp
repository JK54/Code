#include "comm.h"
int count_calls(int i)
{
		static size_t ctr;
		int j = 0;
		i = 5;
		return ++ctr;
}
