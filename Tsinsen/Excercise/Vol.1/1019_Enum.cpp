#include <iostream>

#define LEN 4
#define SOURCE_LEN 4
int main()
{
	char data[SOURCE_LEN] = {'A','B','C','D'};
	char res[LEN];
	int i,j,k,l,m;
	for(i = 0;i < SOURCE_LEN;i++)
	{
		res[LEN - 1] = data[i];
		for(j = 0;j < SOURCE_LEN;j++)
		{
			res[LEN - 2] = data[j];
			for(k = 0;k < SOURCE_LEN;k++)
			{
				res[LEN - 3] = data[k];
				for( l = 0;l < SOURCE_LEN;l++)
				{
					res[LEN - 4] = data[l];
					for(m = LEN - 1;m >= 0;m--)
						std::cout<<res[m];
					std::cout<<std::endl;
				}
			}
		}
	}
	return 0;
}
