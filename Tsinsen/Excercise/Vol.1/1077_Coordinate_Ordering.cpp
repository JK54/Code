#include <iostream>
using namespace std;

struct position 
{
    int x;
    int y;
};

void psort(position ps[], int n)
{
	int i,j,l,p,q,r;
	for(i = 0;i < n;i++)
	{
		j = i;
		for(l = i + 1;l < n;l++)
		{
			if(ps[j].x > ps[l].x)
				j = l;
		}
		std::swap(ps[i].y,ps[j].y);
		std::swap(ps[i].x,ps[j].x);
	}
	for(i = 1;i < n;i++)
	{
		p = i - 1;
		while(i < n && ps[p].x == ps[i].x)
			i++;
		for(j = p;j < i;j++)
		{
			q = j;
			for(r = j + 1;r < i;r++)
			{
				if(ps[q].y > ps[r].y)
					q = r;
			}
			std::swap(ps[q].y,ps[j].y);
		}
	}
}
const int maxn = 100;
position points[maxn];
int n;
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> points[i].x >> points[i].y;
    psort(points, n);
    for (int i = 0; i < n; ++i)
        cout << points[i].x << " " << points[i].y << endl;
    return 0;
}
