#include <iostream>
#include <string.h>
#include <math.h>

std::string hex2bin(char a)
{
	switch(a)
	{
		case('0'):
			return "0000";
		case('1'):
			return "0001";
		case('2'):
			return "0010";
		case('3'):
			return "0011";
		case('4'):
			return "0100";
		case('5'):
			return "0101";
		case('6'):
			return "0110";
		case('7'):
			return "0111";
		case('8'):
			return "1000";
		case('9'):
			return "1001";
		case('A'):
			return "1010";
		case('B'):
			return "1011";
		case('C'):
			return "1100";
		case('D'):
			return "1101";
		case('E'):
			return "1110";
		case('F'):
			return "1111";
	}
	return "";
}

char bin2oct(std::string a)
{
	if(a == "000")
		return '0';
	else if(a == "001")
		return '1';
	else if(a == "010")
		return '2';
	else if(a == "011")
		return '3';
	else if(a == "100")
		return '4';
	else if(a == "101")
		return '5';
	else if(a == "110")
		return '6';
	else
		return '7';
	
}
int main()
{
	int n,i,j,k,hlen,blen;
	char tmp;
	std::string *source,*trans,*result;
	std::cin>>n;
	source = new std::string [n];
	trans = new std::string [n];
	result = new std::string [n];
	for(i = 0;i < n;i++)
	{
		std::cin>>source[i];
		hlen = source[i].length();
		for(j = 0;j < hlen;j++)
			trans[i] += hex2bin(source[i][j]);
		blen = trans[i].length();
		if(blen % 3 == 1)
		{
			k = 1;
			tmp = bin2oct("00" + std::string(trans[i],0,1));
			if(tmp != '0')
				result[i] += tmp;
		}
		else if(blen % 3 == 2)
		{
			k = 2;
			tmp = bin2oct("0" + std::string(trans[i],0,2));
			if(tmp != '0')
				result[i] += tmp;
		}
		else
		{
			k = 3;
			tmp = bin2oct(std::string(trans[i],0,3));
			if(tmp != '0')
				result[i] += tmp;
		}
		for(j = k;j < blen;j += 3)
			result[i] += bin2oct(std::string(trans[i],j,3));
	}
	for(i = 0;i < n;i++)
		std::cout<<result[i]<<std::endl;
	delete [] source;
	delete [] trans;
	delete [] result;
	return 0;
}
