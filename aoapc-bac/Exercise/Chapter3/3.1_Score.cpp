#include <iostream>
#include <cstring>
int main()
{
	int T,tmp,*score,strl;
	int i,j;
	std::string data;
	std::cin>>T;
	score = new int [T];
	std::memset(score,0,sizeof(int) * T);
	for(i = 0;i < T;i++)
	{
		std::cin>>data;
		strl = data.length();
		tmp = 0;
		for(j = 0;j < strl;j++)
		{
			if(data[j] != 'O')
				tmp = 0;
			else
			{
				++tmp;
				score[i] += tmp;
			}
		}
	}
	for(i = 0;i < T;i++)
		std::cout<<score[i]<<std::endl;
	delete [] score;
	return 0;
}
