#include "../Include/AVLTree.hpp"
#include "../Include/RBTree.hpp"
#include "../Include/BSTree.hpp"
#include "Avl.cpp"
#define CW 99
#define TYPE unsigned int

AVLTree<TYPE> avl_h;
AVLtree avl_l;
RBTree<TYPE> rbtree_h;
BSTree<TYPE> bstree_h;
set<TYPE> set0;
#ifdef DDO3
	std::ofstream sta("./Statistics/avl_o3_raw.log");
	std::ofstream stb("./Statistics/avl_o3_avg.log");
#else
	std::ofstream sta("./Statistics/avl_o1_raw.log");
	std::ofstream stb("./Statistics/avl_o1_avg.log");
#endif
struct timeval s0,s1;
double t1,t2,t3;
double t[CW][3];
double total = 0,in = 0,s = 0,r = 0;
TYPE *a = new TYPE[50000000];
long Coo;
void spwan(int x)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
#ifdef DDO3
	std::string name = "./Tmp/randii.txt";
#else
	std::string name = "./Tmp/1/raii.txt";
#endif
	std::random_device rd;
	std::mt19937 mt(rd());
	for(int i = 0;i < CW;i++)
	{
		name[10] = (i + 1) / 10 + '0';
		name[11] = (i + 1) % 10 + '0';
		std::ofstream rd(name);
		for(int j = 0;j < x;j++)
			rd<<mt()<<" ";
		rd.close();
	}
	gettimeofday(&s1,NULL);
	t1 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

void test_avl_han(bool ordered,int x,std::istream &fd)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < x;i++)
		{
			fd>>a[i];
			avl_h.Insert(a[i]);
		}
	}
	else
		for(int i = 0;i < x;i++)
			avl_h.Insert(i);
	Coo += avl_h.Count();
	gettimeofday(&s1,NULL);
	t1 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = x - 1;i >= 0;i--)
			avl_h.Search(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			avl_h.Search(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < x;i++)
			avl_h.Remove(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			avl_h.Remove(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

void test_avl_ld(bool ordered,int x,std::istream &fd)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < x;i++)
		{
			fd>>a[i];
			avl_l.insert(a[i]);
		}
	}
	else
		for(int i = 0;i < x;i++)
			avl_l.insert(i);
	gettimeofday(&s1,NULL);
	t1 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = x - 1;i >= 0;i--)
			avl_l.search(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			avl_l.search(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < x;i++)
			avl_l.erase(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			avl_l.erase(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

void test_rbtree_han(bool ordered,int x,std::istream &fd)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < x;i++)
		{
			fd>>a[i];
			rbtree_h.Insert(a[i]);
		}
	}
	else
		for(int i = 0;i < x;i++)
			rbtree_h.Insert(i);
	gettimeofday(&s1,NULL);
	t1 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = x - 1;i >= 0;i--)
			rbtree_h.Search(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			rbtree_h.Search(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < x;i++)
			rbtree_h.Remove(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			rbtree_h.Remove(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}
void test_bstree_han(bool ordered,int x,std::istream &fd)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < x;i++)
		{
			fd>>a[i];
			bstree_h.Insert(a[i]);
		}
	}
	else
		for(int i = 0;i < x;i++)
			bstree_h.Insert(i);
	gettimeofday(&s1,NULL);
	t1 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = x - 1;i >= 0;i--)
			bstree_h.Search(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			bstree_h.Search(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < x;i++)
			bstree_h.Remove(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			bstree_h.Remove(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}
void test_set(bool ordered,int x,std::istream &fd)
{
	std::ios::sync_with_stdio(false);
	gettimeofday(&s0,NULL);
	if(!ordered)
	{
		for(int i = 0;i < x;i++)
		{
			fd>>a[i];
			set0.insert(a[i]);
		}
	}
	else
		for(int i = 0;i < x;i++)
			set0.insert(i);
	gettimeofday(&s1,NULL);
	t1 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = x - 1;i >= 0;i--)
			set0.find(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			set0.find(i);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*static_cast<double>(s0.tv_sec - s1.tv_sec) + static_cast<double>(s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	if(!ordered)
		for(int i = 0;i < x;i++)
			set0.erase(a[i]);
	else
		for(int i = x - 1;i >= 0;i--)
			set0.erase(i);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*static_cast<double>(s1.tv_sec - s0.tv_sec) + static_cast<double>(s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

double add_row(double data[][3],int row)
{
	double result = 0;
	for(int i = 0;i < 3;i++)
		result += data[row][i];
	return result;
}

double add_col(double data[][3],int col,int n)
{
	double result = 0;
	for(int i = 0;i < n;i++)
		result += data[i][col];
	return result;
}

void test(void f(bool,int,std::istream &),int x,bool ordered)
{
	std::ios::sync_with_stdio(false);
#ifdef DDO3
	std::string name = "./Tmp/randii.txt";
#else
	std::string name = "./Tmp/1/raii.txt";
#endif
	for(int i = 0;i < CW;i++)
	{
		name[10] = (i + 1) / 10 + '0';
		name[11] = (i + 1) % 10 + '0';
		std::ifstream input(name);
		f(ordered,x,input);
		t[i][0] = t1;
		t[i][1] = t2;
		t[i][2] = t3;
		input.close();
	}
	sta<<" wanted   nodes : "<<x<<std::endl;
	sta<<" inserted nodes : "<<static_cast<int>(Coo/CW)<<std::endl;
	sta<<"\t\t"<<"Insert time(s)"<<"\t\t"<<"Search time(s)"<<"\t\t"<<"Remove time(s)"<<"\t\t"<<"Total  time(s)"<<std::endl;
	stb<<" wanted   nodes : "<<x<<std::endl;
	stb<<" inserted nodes : "<<static_cast<int>(Coo/CW)<<std::endl;
	stb<<"\t\t"<<"Insert time(s)"<<"\t\t"<<"Search time(s)"<<"\t\t"<<"Remove time(s)"<<"\t\t"<<"Total  time(s)"<<std::endl;
	for(int i = 0;i < CW;i++)
		sta<<std::fixed<<std::setprecision(6)<<" "<<(i + 1)<<"\t\t"<<t[i][0]<<"\t\t\t"<<t[i][1]<<"\t\t\t"<<t[i][2]<<"\t\t\t"<<add_row(t,i)<<std::endl;
	sta<<std::endl;
	in = add_col(t,0,CW);
	s = add_col(t,1,CW);
	r = add_col(t,2,CW);
	total = in + s + r;
	sta<<std::fixed<<std::setprecision(6)<<" Total "<<"\t"<<in<<"\t\t\t"<<s<<"\t\t\t"<<r<<"\t\t\t"<<total<<std::endl;
	sta<<std::fixed<<std::setprecision(6)<<" Avg "<<"\t"<<static_cast<double>(in/CW)<<"\t\t\t"<<static_cast<double>(s/CW)<<"\t\t\t"<<static_cast<double>(r/CW)<<"\t\t\t"<<static_cast<double>(total/CW)<<"\t\t\t"<<"\n\n"<<std::endl;
	stb<<std::fixed<<std::setprecision(6)<<" Avg "<<"\t"<<static_cast<double>(in/CW)<<"\t\t\t"<<static_cast<double>(s/CW)<<"\t\t\t"<<static_cast<double>(r/CW)<<"\t\t\t"<<static_cast<double>(total/CW)<<"\t\t\t"<<"\n\n"<<std::endl;
}

void test_u(int x)
{
	std::ios::sync_with_stdio(false);
	Coo = 0;
	spwan(x);
	sta<<"-----------------------------------------------------------------------------------------------------"<<std::endl;
	stb<<"----------------------------------------------------------------------------------------------------"<<std::endl;
	sta<<"Generate rand time : "<<t1<<" s"<<std::endl;
	sta<<"\t\t\t\t\t\t\t\t\t\tAVLTree_Han(Disordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tAVLTree_Han(Disordered)"<<std::endl;
	test(test_avl_han,x,0);
	sta<<"\t\t\t\t\t\t\t\t\t\tAVLTree_LD(Disordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tAVLTree_LD(Disordered)"<<std::endl;
	test(test_avl_ld,x,0);
	sta<<"\t\t\t\t\t\t\t\t\t\tRBTree_Han(Disordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tRBTree_Han(Disordered)"<<std::endl;
	test(test_rbtree_han,x,0);
	sta<<"\t\t\t\t\t\t\t\t\t\tBSTree_Han(Disordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tBSTree_Han(Disordered)"<<std::endl;
	test(test_bstree_han,x,0);
	sta<<"\t\t\t\t\t\t\t\t\t\tSet(Disordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tSet(Disordered)"<<std::endl;
	test(test_set,x,0);
	Coo = 0;
	sta<<"\t\t\t\t\t\t\t\t\t\tAVLTree_Han(Ordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tAVLTree_Han(Ordered)"<<std::endl;
	test(test_avl_han,x,1);
	sta<<"\t\t\t\t\t\t\t\t\t\tAVLTree_LD(Ordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tAVLTree_LD(Ordered)"<<std::endl;
	test(test_avl_ld,x,1);
	sta<<"\t\t\t\t\t\t\t\t\t\tRBTree_Han(Ordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tRBTree_Han(Ordered)"<<std::endl;
	test(test_rbtree_han,x,1);
	if(x <= 100000)
	{
		sta<<"\t\t\t\t\t\t\t\t\t\tBSTree_Han(Ordered)"<<std::endl;
		stb<<"\t\t\t\t\t\t\t\t\t\tBSTree_Han(Ordered)"<<std::endl;
		test(test_bstree_han,x,1);
	}
	sta<<"\t\t\t\t\t\t\t\t\t\tSet(Ordered)"<<std::endl;
	stb<<"\t\t\t\t\t\t\t\t\t\tSet(Ordered)"<<std::endl;
	test(test_set,x,1);
}

int main()
{
	test_u(1000);
	test_u(10000);
	test_u(100000);
	test_u(1000000);
	test_u(5000000);
	test_u(10000000);
	test_u(20000000);
	test_u(30000000);
	test_u(40000000);
	test_u(50000000);
	test_u(100000000);
	delete [] a;
	return 0;
}
