#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

int maxproduct1(int len)
{
	if(len < 2)
		return 0;
	if(len == 2)
		return 1;
	if(len == 3)
		return 2;
	int products[len],maxp;
	products[0] = 0,products[1] = 1,products[2] = 2,products[3] = 3;
	for(int i = 4;i <= len;i++)
	{
		maxp = 0;
		for(int j = 1;j <= i/2;j++)
		{
			int product = products[j] * products[i - j];
			if(maxp < product)
				maxp = product;
		}
		products[i] = maxp;
	}
	maxp = products[len];
	return maxp;
}

int maxproduct2(int len)
{
	if(len <= 3)
		return maxproduct1(len);
	int factor2,factor3 = len / 3;
	if(len - factor3 * 3 == 1)
		factor3--;
	factor2 = (len - factor3 * 3) / 2;
	return pow(2,factor2) * pow(3,factor3);

}
int main()
{
	int len,maxp;
	cin>>len;
	maxp = maxproduct2(len);
	cout<<maxp<<endl;
}
