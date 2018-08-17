#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include<ctime>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 1000000
using namespace std;

struct AVLNode {
	int data;
	int height;
	AVLNode *Lchild;
	AVLNode *Rchild;
};

int getHeight(AVLNode *p) {
	if (!p)
		return 0;
	else
		return p->height;
}

int getBalanceFactor(AVLNode *p) {
	return getHeight(p->Lchild) - getHeight(p->Rchild);
}

void updateHeight(AVLNode *p) {
	p->height = max(getHeight(p->Lchild), getHeight(p->Rchild)) + 1;
}

AVLNode *search(AVLNode *T, int x) {
	if (!T)
		return nullptr;
	if (x == T->data)
		return T;
	if (x<T->data)
		return search(T->Lchild, x);
	return search(T->Rchild, x);
}

void L(AVLNode *&T) {
	AVLNode *p = T->Rchild;
	AVLNode *q = T;
	T = p;
	q->Rchild = p->Lchild;
	p->Lchild = q;
	updateHeight(q);
	updateHeight(p);
	// AVLNode *temp = T->Rchild;
	// T->Rchild = temp->Lchild;
	// temp->Lchild = T;
	// updateHeight(T);
	// updateHeight(temp);
	// T = temp;
}

void R(AVLNode *&T) {
	AVLNode *lc = T->Lchild;
	AVLNode *p = T;
	T = lc;
	p->Lchild = lc->Rchild;
	lc->Rchild = p;
	updateHeight(p);
	updateHeight(lc);
	// AVLNode *temp = T->Lchild;
	// T->Lchild = temp->Rchild;
	// temp->Rchild = T;
	// updateHeight(T);
	// updateHeight(temp);
	// T = temp;
}

void insert(AVLNode *&T, int v) {
	if (!T) {
		T = new AVLNode;
		T->height = 1;
		T->data = v;
		T->Lchild = nullptr;
		T->Rchild = nullptr;
		return;
	}

	if (v<T->data) {
		insert(T->Lchild, v);
		updateHeight(T);
		 if(getBalanceFactor(T)==2){
		     if(getBalanceFactor(T->Lchild)==1)
		         R(T);
		     else{
		         L(T->Lchild);
		         R(T);
		     }
		 }
	}
	else if (v>T->data) {
		insert(T->Rchild, v);
		updateHeight(T);
		 if(getBalanceFactor(T)==-2){
		     if(getBalanceFactor(T->Rchild)==-1)
		         L(T);
		     else{
		         R(T->Rchild);
		         L(T);
		     }
		 }
	}
}

void del(AVLNode *&T, int x) {
	if (!T)
		return;
	if (T->data<x) {
		del(T->Rchild, x);
		updateHeight(T);
		if (getBalanceFactor(T) == 2) {
			if (getBalanceFactor(T->Lchild) !=-1 )
				R(T);
			else {
				L(T->Lchild);
				R(T);
			}
		}
		return;
	}
	else if (T->data>x) {
		del(T->Lchild, x);
		updateHeight(T);
		if (getBalanceFactor(T) == -2) {
			if (getBalanceFactor(T->Rchild) !=1)
				L(T);
			else {
				R(T->Rchild);
				L(T);
			}
		}
		return;
	}
	else {
		if (!T->Lchild) {
			T = T->Rchild;
			return;
		}
		else if (!T->Rchild) {
			T = T->Lchild;
			return;
		}
		AVLNode *p = T->Lchild, *pre = T;
		while (p->Rchild) {
			pre = p;
			p = p->Rchild;
		}
		T->data = p->data;
		del(T->Lchild, T->data);
		updateHeight(T);
		if (getBalanceFactor(T) == -2) {
			if (getBalanceFactor(T->Rchild) != 1)
				L(T);
			else {
				R(T->Rchild);
				L(T);
			}
		}
		return;
	}
}


AVLNode *Creat(vector<int> iv) {
	AVLNode *T = nullptr;
	for (auto c : iv) {
		insert(T, c);
	}
	return T;
}

AVLNode *Creat() {
	AVLNode *T = nullptr;
	srand(time(0));

	for (int i = 0; i < 50000;++i) {
		int x = rand();
		insert(T, x);
	}
	return T;
}

void Inorder(AVLNode *T) {
	if (!T)
		return;

	Inorder(T->Lchild);
	cout << T->data << " ";

	Inorder(T->Rchild);
}

void Print(AVLNode *T) {
	if (!T)
		return;
	cout << char('a' - 1 + T->data);
	if (!T->Lchild && !T->Rchild)
		return;
	cout << "(";
	Print(T->Lchild);
	cout << ",";
	Print(T->Rchild);
	cout << ")";
}

bool Search(AVLNode *T,int vle)
{
	AVLNode *trav;
	trav = T;
	while(trav != nullptr)
	{
		if(trav->data == vle)
			return true;
		else if(trav->data > vle)
			trav = trav->Lchild;
		else
			trav = trav->Rchild;
	}
	return false;
}

double t1,t2,t3;
struct timeval s0,s1;
int fd = open("/dev/urandom",O_RDONLY);
std::ofstream op("avl_l.log");
void test() {
	vector<int> iv;
	iv.reserve(N);
	AVLNode *T = nullptr;
	gettimeofday(&s0,NULL);
	for (int i = 0; i < N; ++i) 
	{
		read(fd,&iv[i],sizeof(int));
		insert(T,iv[i]);
	}
	gettimeofday(&s1,NULL);
	t1 = ((1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0));
	for(int i = 0; i < N;i++)
		Search(T,iv[i]);
	gettimeofday(&s0,NULL);
	t2 = ((1000.0*(s0.tv_sec - s1.tv_sec) + (s0.tv_usec - s1.tv_usec)/1000.0));
	for (int i = 0; i < N; ++i)
		del(T, iv[i]);
	gettimeofday(&s1,NULL);
	t3 = ((1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0));
}

int main()
{
	double t[10];
	double s = 0;
	for(int i = 1;i <= 10;i++)
	{
		test();
		t[i] = t1 + t2 + t3;
		op<<i<<'\n'<<"Insert time : "<<t1<<"ms\n"<<"Search time : "<<t2<<"ms\n"<<"Remove time : "<<t3<<"ms\n"<<"Total  time : "<<t[i]<<"ms\n"<<std::endl;
		s += t[i];
	}
	op<<"All cost : "<<(static_cast<int>(s / 1000)) <<"s"<<(static_cast<int>(s) % 1000)<<"ms"<<std::endl;
	close(fd);
	return 0;
}
