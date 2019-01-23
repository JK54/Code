#include "comm.h"

using namespace std;

template<typename T>
int compare(T &v1,T &v2)
{
	if(v2 < v1)
		return 1;
	if(v1 < v2)
		return -1;
	return 0;
}

