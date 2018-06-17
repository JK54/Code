#include <iostream>

void maxmin_0(int a,int b,int c,int *max,int *min)
{
	*max = *min = b;
	if(b < c)
		*max = c;
	if(b > a)
		*min = a;
	else	
		*max = a;
}
void maxmin_1(int a,int b,int c,int &max,int &min)
{
	a > b ? (b > c ? min = c,max = a:(a > c ? max = a,min = b : max = c,min = a)) : (c < a ? min = c,max = b : b > c ? max = b,min = a: max = c,min = a);
}
int main()
{
    int a, b, c, se, min, max;
    std::cin >> a >> b >> c >> se;
    if (se == 0)
		maxmin_0(a, b, c, &max, &min);
    else
		maxmin_1(a, b, c, max, min);
    std::cout << max << ' ' << min << std::endl;
	return 0;
}
