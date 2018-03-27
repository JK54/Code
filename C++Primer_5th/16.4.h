#include "comm.h"
template<typename T1,typename T2>
T1 findl(const T1 begin,const T1 end,const T2 &value)
{
	for(auto Iter = begin; Iter != end; ++Iter)
	{
		std::cout<<"round"<<":"<<*Iter<<std::endl;
		if(*Iter == value)
		{
			std::cout<<"FFFFF"<<std::endl;
			return Iter;
		}
	}
	std::cout<<"not found"<<std::endl;
	return end;
}
/*
 * 
 * template<typename Iterator, typename Value>
 * Iterator fnd(Iterator first, Iterator last, const Value& v)
 * {
 *     for ( ; first != last && *first != v; ++first);
 *     std::cout <<"asdasd"<<std::endl;
 *     return first;
 * }
 */
