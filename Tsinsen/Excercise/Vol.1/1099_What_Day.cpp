#include <iostream>
#include <string.h>
void format(std::string& str)
{
    int len = str.length();
    str[0] = toupper(str[0]);
    for (int i = 1; i < len; i++)
	str[i] = tolower(str[i]);
}
int find(std::string tmp, std::string* data, int n)
{
    int i;
    for (i = 0; i < n; i++)
	if (tmp == data[i])
	    return i;
    return -1;
}
void judge(std::string data[8][2], std::string* result)
{
    int i;
    int s = 7;
    bool res[7];
    memset(res,true, 7);
    for (i = 0; i < 8; i++) 
	{
		if (data[i][0] != data[i][1])
		{
	    	res[find(data[i][0], result, s)] = false;
	    	res[find(data[i][1], result, s)] = false;
		}
	}
    for (i = 0; i < s; i++)
		if (res[i] == true)
		{
	    	std::cout << result[i] << std::endl;
			break;
		}
}
int main()
{
    std::string data[8][2];
    std::string result[] = { "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday", "Sunday" };
    std::string tmp;
    int i, j;
    for (i = 0; i < 8; i++) {
	for (j = 0; j < 2; j++) {
	    std::cin >> tmp;
	    format(tmp);
	    data[i][j] = tmp;
	}
    }
    judge(data, result);
    return 0;
}
