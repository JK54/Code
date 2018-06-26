#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

char s[110];

bool check(int i, int j)
{
    int L = (j - i + 1) / 2;
    for (int k = i; k <= i + L - 1; k++)
	if (s[k] != s[k + L])
	    return false;
    return true;
}

int main()
{
    scanf("%s", s);
    int lenn = strlen(s);
    for (int k = lenn - (lenn % 2); k >= 0; k -= 2)
	for (int i = 0; i <= lenn - k; i++) {
	    int j = i + k - 1;
	    if (check(i, j)) {
		printf("%d", k);
		return 0;
	    }
	}
    return 0;
}
