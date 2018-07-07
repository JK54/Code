#include <iostream>
#include <sstream>
std::string to_string(int n)
{
	std::string result;
	std::ostringstream os;
	os<<n;
	result = os.str();
	return result;
}

void An(int i,int n,int ng,std::string &str)
{
	if(i > n)
		return;
	str += "sin(";
	str += to_string(i);
	if(i < n)
		str += (ng == -1? "-":"+");
	An(i + 1,n,ng * (-1),str);
	str +=")";
}
void Sn(std::string &result,int n)
{
	std::string tmp;
	An(1,1,-1,result);
	result += "+" + to_string(n);
	for(int i = 2;i <= n;i++)
	{
		An(1,i,-1,tmp);
		result = "(" + result + ")" + tmp + "+" + to_string(n - i + 1);
		tmp = "";
	}
	std::cout<<result<<std::endl;
}
int main()
{
	int n;
	std::string result;
	std::cin>>n;
	Sn(result,n);
	return 0;
}
