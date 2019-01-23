#include <iostream>

void handledata(int n,int m,int *k,int *s)
{
	int i,j,l,p,q,r;
	int num;
	for(i = 0;i < n;i++)
	{
		j = i;
		for(l = i + 1;l < n;l++)
		{
			if(s[j] < s[l])
				j = l;
		}
		std::swap(k[i],k[j]);
		std::swap(s[i],s[j]);
	}
	for(i = 1;i < n;i++)
	{
		p = i - 1;
		while(i < n && s[p] == s[i])
			i++;
		for(j = p;j < i;j++)
		{
			q = j;
			for(r = j + 1;r < i;r++)
			{
				if(k[q] > k[r])
					q = r;
			}
			std::swap(k[q],k[j]);
		}
	}
	num = 1.5 * m;
	for(i = num;i < n;i++)
	{
		if(s[num - 1] == s[i])
			num++;
		else if(s[num - 1] > s[i])
			break;
	}
	std::cout<<s[num - 1]<<" "<<num<<std::endl;
	for(i = 0;i < num;i++)
		std::cout<<k[i]<<" "<<s[i]<<std::endl;
}

int main()
{
	int n,m,*k,*s;
	int i;
	std::cin>>n>>m;
	k = new int[n];
	s = new int[n];
	for(i = 0;i < n;i++)
		std::cin>>k[i]>>s[i];
	handledata(n,m,k,s);
	delete [] k;
	delete [] s;
	return 0;
}
