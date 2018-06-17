#include <iostream>

void draw(int n)
{
	int i,j;
	//left,right,up,down ,flag of direction
	bool l,r,u,d;
	l = r = u = d = false;
	int **data = new int *[n];
	for(i = 0;i < n;i++)
		data[i] = new int [n];
	for(i = 1;i <= 2 * n - 1;i++)
	{
		if(r == true)
			r = false,d = true;
		else if(d == true)
			d = false,l = true;
		else if(l == true)
			l = false,u = true;
		else if(u == true)
			u = false,d = true;
		else
			//the first round.
			d = true;
		//
		if(r == true || l == true)
		{
		
		}
		//
		else if(u == true || d == true)
		{
		
		}
	}
}

int main()
{
	int n;
	std::cin>>n;
	draw(n);
	return 0;
}
