#include "comm.h"

template<typename Iterator,unsigned N>

Iterator* beginl(Iterator (&p)[N])
{
	return p;
}

template<typename Iterator,unsigned N>
Iterator* enid(Iterator (&p)[N])
{
	return p+N;
}
