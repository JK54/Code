#include <iostream>

struct BBA
{
	std::string name;
	int id;
	int score;
	int profit;
	int raw;
};

void swap(std::string &a,std::string &b)
{
	std::string tmp;
	tmp = a;
	a = b;
	b = tmp;
}
void ranking(std::string *ranked,struct BBA* data,int n)
{
	int i,j;
	std::string tmp;
	//init ranked array
	for(i = 0;i < n;i++)
		ranked[i] = data[i].name;
	for(i = 0; i < n;i++)
	{
		for(j = i + 1;j < n;j++)
		{
			if(data[i].score < data[j].score)
				swap(ranked[i],ranked[j]);
			else if(data[i].score == data[j].score)
			{
				if(data[i].profit <data[j].profit)
					swap(ranked[i],ranked[j]);
				else if(data[i].profit == data[j].profit)
				{
					if(data[i].raw < data[j].raw)
						swap(ranked[i],ranked[j]);
					else if(data[i].raw == data[j].raw)
						if(data[i].name > data[j].name)
							swap(ranked[i],ranked[j]);
				}
			}
		}
	}
}
int main()
{
	int i,n;
	struct BBA* data;
	std::string *ranked;
	std::cin>>n;
	data = new struct BBA [n];
	ranked = new std::string [n];
	for(i = 0;i < n;data[i].id = i,i++)
		std::cin>>data[i].name>>data[i].score>>data[i].profit>>data[i].raw;
	ranking(ranked,data,n);
	for(i = 0;i < n;i++)
		std::cout<<ranked[i]<<std::endl;
	delete [] data;
	delete [] ranked;
	return 0;
}
