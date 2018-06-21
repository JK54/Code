#include <iostream>

int max(int a,int b,int c,int d)
{
	return std::max(std::max(a,b),std::max(c,d));
}

void check_dna(std::string *data, int n, std::string &result)
{
	int i,j,len;
	int counta,countc,countg,countt;
	len = static_cast<int>(data[0].length());
	for(i = 0; i < len; i++)
	{
		counta = countc = countg = countt = 0;
		for(j = 0; j < n; j++)
		{
			if (data[j][i] == 'A')
				counta++;
			else if (data[j][i] == 'C')
				countc++;
			else if(data[j][i] == 'G')
				countg++;
			else
				countt++;
		}
		if (counta == max(counta,countc,countg,countt))
			result += "A";
		else if (countc == max(counta,countc,countg,countt))
			result += "C";
		else if (countg == max(counta,countc,countg,countt))
			result += "G";
		else if (countt == max(counta,countc,countg,countt))
			result += "T";
	}
	std::cout<<result<<std::endl;
}

int main()
{
	int n,i;
	std::string *data,result;
	std::cin>>n;
	data = new std::string [n];
	for (i = 0; i < n; i++)
		std::cin>>data[i];
	check_dna(data,n,result);
	delete [] data;
	return 0;
}
