#include <iostream>

int main()
{
	char a[30];
	int aa = 333333;
	snprintf(a,sizeof(a),"%d",aa);
	std::cout<<a<<std::endl;
}
