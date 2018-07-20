#include <iostream>

void pstring(int N,std::string *data)
{
	int i,j,k,f,strlen,*period;
	period = new int [N];
	for(i = 0;i < N;i++)
	{
		strlen = data[i].length();
		for(j = 1;j <= strlen/2;j++)
		{
			for(k = 0,f = 0;k < strlen - j;k += j)
				if(std::string(data[i],k,j) != std::string(data[i],k + j,j))
				{
					f = 1;
					break;
				}
			if(f == 0)
			{
				period[i] = j;
				break;
			}
		}
		if(j > strlen/2)
			period[i] = strlen;
	}
	for(i = 0;i < N - 1;i++)
		std::cout<<period[i]<<std::endl<<std::endl;
	std::cout<<period[i]<<std::endl;
	delete [] period;
}
int main()
{
	int N;
	std::string *data;
	std::cin>>N;
	data = new std::string [N];
	for(int i = 0;i < N;i++)
		std::cin>>data[i];
	pstring(N,data);
	return 0;
}
