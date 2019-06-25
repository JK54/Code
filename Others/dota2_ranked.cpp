#include <iostream>
#include <vector>
#include <algorithm>

class heroes
{
	public:
		heroes(int pos,int levl,int rate):pos(pos),level(levl),rate(rate){}
		heroes():pos(0),level(0),rate(0.0){}
		int positon(){return pos;}
		int ranked_level(){return level;}
		float winning_rate(){return rate;}
	private:
		int pos;
		int level;
		float rate;
};


int main()
{
}
