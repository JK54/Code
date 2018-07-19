#include <iostream>
#include <string>
#include <cstring>
#define DEFAULT_SIZE 5

bool input(std::istream &is,char block[][DEFAULT_SIZE],char op[],int &count)
{
	std::string tmp;
	int i,j,strl;
	std::getline(is,tmp);
	strl = tmp.length();
	if(strl == 1 && tmp[strl - 1] == 'Z')
		return false;
	else
	{
		for(j = 0;j < DEFAULT_SIZE;j++)
			block[0][j] = tmp[j];
		for(i = 1;i < DEFAULT_SIZE;i++)
		{
			std::getline(is,tmp);
			for(j = 0;j < DEFAULT_SIZE;j++)
				block[i][j] = tmp[j];
		}
		i = 0;
		while(getline(is,tmp))
		{
			for(j = 0;tmp[j] != '\0' && tmp[j] != '0';i++,j++)
				op[i] = tmp[j];
			if(tmp[j] == '0')
				break;
		}
	}
	op[i] = '\0';
	count++;
	return true;
}
void output(char block[][DEFAULT_SIZE],char op[],int count)
{
	bool flag;
	int i,j,x0,y0;
	flag = true;
	for(i = 0,x0 = -1;x0 == -1 && i < DEFAULT_SIZE;i++)
		for(j = 0,y0 = -1;y0 == -1 && j < DEFAULT_SIZE;j++)
			if(block[i][j] == ' ')
				x0 = i,y0 = j;
	for(i = 0;op[i] != '\0' && flag == true;i++)
	{
		if(op[i] == 'A')
		{
			if(x0 == 0)
				flag = false;
			else
			{
				std::swap(block[x0 - 1][y0],block[x0][y0]);
				x0--;
			}
		}
		else if(op[i] == 'B')
		{
			if(x0 == DEFAULT_SIZE - 1)
				flag = false;
			else
			{
				std::swap(block[x0 + 1][y0],block[x0][y0]);
				x0++;
			}
		}
		else if(op[i] == 'L')
		{
			if(y0 == 0)
				flag = false;
			else
			{	
				std::swap(block[x0][y0 - 1],block[x0][y0]);
				y0--;
			}
		}
		else if(op[i] == 'R')
		{
			if(y0 == DEFAULT_SIZE - 1)
				flag = false;
			else
			{
				std::swap(block[x0][y0 + 1],block[x0][y0]);
				y0++;
			}
		}
		else
			flag = false;
	}
	std::cout<<"Puzzle #"<<count<<":"<<std::endl;
	if(flag == false)
		std::cout<<"This puzzle has no final configuration.";
	else
	{
		for(i = 0;i < DEFAULT_SIZE - 1;i++)
		{
			for(j = 0;j < DEFAULT_SIZE - 1;j++)
				std::cout<<block[i][j]<<" ";
			std::cout<<block[i][j]<<std::endl;
		}
		for(j = 0;j < DEFAULT_SIZE - 1;j++)
			std::cout<<block[i][j]<<" ";
		std::cout<<block[i][j];
	}
}
int main()
{
	char block[DEFAULT_SIZE][DEFAULT_SIZE],op[100];
	int count = 0;
	std::memset(op,'\0',sizeof(char) * 100);
	input(std::cin,block,op,count);
	output(block,op,count);
	while(input(std::cin,block,op,count))
	{
		std::cout<<std::endl<<std::endl;
		output(block,op,count);
	}
	return 0;
}
