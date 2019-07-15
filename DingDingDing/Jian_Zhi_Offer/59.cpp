#include <iostream>
#include <random>
#include <deque>
using std::vector;

vector<int> slidemax(int data[],int len,int winsize)
{
	vector<int> wmax;
	if(data == nullptr || len <= 0 || winsize > len)
		return wmax;
	for(int i = 0;i <= len - winsize;i++)
	{
		int winmax = data[i];
		for(int j = i + 1;j < i + winsize;j++)
			if(winmax < data[j])
				winmax = data[j];
		wmax.push_back(winmax);
	}
	return wmax;
}

vector<int> slidemax2(int data[],int len,int winsize)
{
	vector<int> winmax;
	if(data == nullptr || len <= 0 || winsize > len || winsize <= 1)
		return winmax;
	std::deque<int> queue;
	for(int i = 0;i < winsize;i++)
	{
		while(!queue.empty() && data[i] >= data[queue.back()])
			queue.pop_back();
		queue.push_back(i);
	}
	winmax.push_back(data[queue.front()]);
	for(int i = winsize;i < len;i++)
	{
		while(!queue.empty() && data[i] >= data[queue.back()])
			queue.pop_back();
		if(!queue.empty() && queue.front() <= (i - winsize))
			queue.pop_front();
		queue.push_back(i);
		winmax.push_back(data[queue.front()]);
	}
	return winmax;

}
int main()
{
	int n = 2000;
	int winsize = 30;
	std::mt19937 mt(std::random_device {}());
	int data[n];
	for(int i = 0;i < n;i++)
	{
		data[i] = mt() % n;
		// std::cout<<data[i]<<" ";
	}
	// std::cout<<std::endl<<std::endl;
	vector<int> aa(slidemax(data,n,winsize));
	vector<int> bb(slidemax2(data,n,winsize));
	for(int i = 0;i < aa.size();i++)
		if(aa[i] != bb[i])
			std::cout<<"dididididi"<<std::endl;
	return 0;
}
