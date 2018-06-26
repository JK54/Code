#include <iostream>

int main()
{
	int i,result[26] = {0};
	std::string source;
	std::cin>>source;
	for(std::string::iterator p = source.begin();p != source.end();p++)
		result[*p - 'a']++;
	for(i = 0;i < 26;i++)
		if(result[i] != 0)
			std::cout<<static_cast<char>('a' + i)<<"\t"<<result[i]<<std::endl;
	return 0;
}
