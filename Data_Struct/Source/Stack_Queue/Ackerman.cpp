#include "../../Include/Stack.hpp"

int akm_nr(int m,int n)
{
	if( m == 0)
		return n + 1;
	else if( m != 0 && n == 0)
		return akm_nr(m-1,1);
	else
		return akm_nr(m-1,akm_nr(m,n-1));
}

int main()
{
	std::cout<<akm_nr(4,5)<<std::endl;
}
