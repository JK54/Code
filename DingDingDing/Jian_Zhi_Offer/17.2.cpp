#include <iostream>
#include <cstring>

void disp(char *numbers,int len)
{
	int offset = -1;
	for(int i = 0;offset == -1 && i < len;i++)
		if(numbers[i] != '0')
			offset = i;
	std::cout<<numbers + offset<<std::endl;
}

/* void perm(char *numbers,int index,int len) */
// {
	// if(index == len - 1)
		// disp(numbers,len);
	// else
	// {
		// for(int i = 0;i < 10;i++)
		// {
			// numbers[index + 1] = i + '0';
			// perm(numbers,index + 1,len);
		// }
	// }
/* } */

void perm2(char *numbers,int index,int len)
{
	if(index == len)
		disp(numbers,len);
	else
	{
		for(int i = 0;i < 10;i++)
		{
			numbers[index] = i + '0';
			perm2(numbers,index + 1,len);
		}
	}
}

void ppp(int len)
{
	if(len <= 0)
		return;
	char numbers[len + 1];
	memset(numbers,'0',len * sizeof(char));
	numbers[len] = '\0';
	perm2(numbers,0,len);
   
	/*  for(int i = 0 ;i < 10;i++) */
	// {
		// numbers[0] = i + '0';
		// perm(numbers,0,len);
	/* } */
}

int main()
{
	int n;
	std::cin>>n;
	ppp(n);
}
