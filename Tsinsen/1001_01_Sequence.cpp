#include <iostream>
#include <bitset>
int main()
{
	// method 1
	int A = 0;
	while(A < 64)
		std::cout<<std::bitset<6>(A++)<<std::endl;
	//method 2
   /*  int i ,j; */
	// for(i =  0;i < 64; i++)
	// {
		// for(j = 5; j >= 0 ;j--)
			// std::cout<<((i>>j) & 1);
		// std::cout<<std::endl;
	/* } */
	return 0;
}
