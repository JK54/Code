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

using namespace std;

struct AVLNode {
	AVLNode(int x) :data(x) {};
	int data;
	int height = 1;
	AVLNode *Lchild = 0;
	AVLNode *Rchild = 0;
};

class AVLtree {
public:
	AVLtree() :root(0), count(0) {};
	AVLtree(const AVLtree &T) = delete;
	~AVLtree() { destroy(root); }
	AVLNode *search(int x);
	bool insert(int x) { return insert(root, x); }
	bool erase(int x) { return erase(root, x); }
	void PreOrder() { PreOrder(root); }
	int size() { return count; }
private:
	AVLNode * root;
	int count;
	bool insert(AVLNode *&T, int x);
	bool erase(AVLNode *&T, int x);
	int getHeight(AVLNode *p);
	void updateHeight(AVLNode *p);
	int bf(AVLNode *p);
	void L(AVLNode *&T);
	void R(AVLNode *&T);
	void RL(AVLNode *&T);
	void LR(AVLNode *&T);
	void Rebalance(AVLNode *&T);
	void PreOrder(AVLNode *p);
	void destroy(AVLNode *&T) {
		if (!T)
			return;
		destroy(T->Lchild);
		destroy(T->Rchild);
		delete(T);
		T = nullptr;
	}
};

int AVLtree::getHeight(AVLNode *p) {
	if (!p)
		return 0;
	else
		return p->height;
}
void AVLtree::updateHeight(AVLNode *p) {
	if (!p)
		return;
	p->height = max(getHeight(p->Lchild), getHeight(p->Rchild)) + 1;
}
int AVLtree::bf(AVLNode *p) {
	return getHeight(p->Lchild) - getHeight(p->Rchild);
}
void AVLtree::L(AVLNode *&T) {
	AVLNode *p = T->Rchild;
	T->Rchild = p->Lchild;
	p->Lchild = T;
	updateHeight(T);
	updateHeight(p);
	T = p;
}
void AVLtree::R(AVLNode *&T) {
	AVLNode *p = T->Lchild;
	T->Lchild = p->Rchild;
	p->Rchild = T;
	updateHeight(T);
	updateHeight(p);
	T = p;
}
void AVLtree::LR(AVLNode *&T) {
	L(T->Lchild);
	R(T);
}
void AVLtree::RL(AVLNode *&T) {
	R(T->Rchild);
	L(T);
}
void AVLtree::Rebalance(AVLNode *&T) {
	if (bf(T) == 2) {
		if (bf(T->Lchild) == -1)
			LR(T);
		else
			R(T);
	}
	else if (bf(T) == -2) {
		if (bf(T->Rchild) == 1)
			RL(T);
		else
			L(T);
	}
}
void AVLtree::PreOrder(AVLNode *p) {
	if (!p)
		return;
	PreOrder(p->Lchild);
	cout << p->data << "(" << p->height << ")";
	PreOrder(p->Rchild);
}
AVLNode *AVLtree::search(int x) {
	AVLNode *p = root;
	while (p) {
		if (p->data > x)
			p = p->Lchild;
		else if (p->data < x)
			p = p->Rchild;
		else
			return p;
	}
	return p;
}

//bool AVLtree::insert(int x) {
//	AVLNode *f = nullptr,*p = root;
//	stack<AVLNode*> s;
//	while (p) {
//		s.push(p);
//		f = p;
//		if (p->data > x)
//			p = p->Lchild;
//		else if (p->data < x)
//			p = p->Rchild;
//		else
//			return 0;
//	}
//	++count;
//	p = new AVLNode(x);
//	if (!root) {
//		root = p;
//		return 1;
//	}
//	if (f->data > x)
//		f->Lchild = p;
//	else
//		f->Rchild = p;
//	while (s.count()) {
//		f = s.top();
//		s.pop();
//		updateHeight(f);
//		if (abs(bf(f)) > 1) {
//			Rebalance(f);
//			if (s.count()) {
//				if (f->data > s.top()->data)
//					s.top()->Rchild = f;
//				else
//					s.top()->Lchild = f;
//			}
//			else
//				root = f;
//		}
//	}
//	return 1;
//}

bool AVLtree::insert(AVLNode *&T, int x) {
	if (!T) {
		T = new AVLNode(x);
		++count;
		return 1;
	}
	if (T->data == x)
		return 0;
	bool b;
	if (T->data < x)
		b = insert(T->Rchild, x);
	else
		b = insert(T->Lchild, x);
	if (b&&T->height != max(getHeight(T->Lchild), getHeight(T->Rchild)) + 1) {
		updateHeight(T);
		if (abs(bf(T)) > 1)
			Rebalance(T);
	}
	return b;
}
//bool AVLtree::erase(int x) {
//	AVLNode *f = nullptr, *p = root;
//	stack<AVLNode*> s;
//	while (p&&p->data != x) {
//		s.push(p);
//		f = p;
//		if (p->data > x)
//			p = p->Lchild;
//		else if (p->data < x)
//			p = p->Rchild;
//	}
//	if (!p)
//		return 0;
//	--count;
//	if (!p->Lchild) {
//		if (!f) {
//			root = p->Rchild;
//			delete p;
//			return 1;
//		}
//		else if (f->data < x) {
//			p = p->Rchild;
//			delete f->Rchild;
//			f->Rchild = p;
//		}
//		else {
//			p = p->Rchild;
//			delete f->Lchild;
//			f->Lchild = p;
//		}
//	}
//	else if (!p->Rchild) {
//		if (!f) {
//			root = p->Rchild;
//			delete p;
//			return 1;
//		}
//		else if (f->data < x) {
//			p = p->Lchild;
//			delete f->Rchild;
//			f->Rchild = p;
//		}
//		else {
//			p = p->Lchild;
//			delete f->Lchild;
//			f->Lchild = p;
//		}
//	}
//	else {
//		AVLNode *q = p;
//		f = p;
//		p = p->Lchild;
//		s.push(f);
//		while (p->Rchild) {
//			f = p;
//			s.push(f);
//			p = p->Rchild;
//		}
//		q->data = p->data;
//		if (f->Lchild == p) {
//			p = p->Lchild;
//			delete f->Lchild;
//			f->Lchild = p;
//		}
//		else {
//			p = p->Lchild;
//			delete f->Rchild;
//			f->Rchild = p;
//		}
//	}
//	while (s.size()) {
//		f = s.top();
//		s.pop();
//		updateHeight(f);
//		if (abs(bf(f)) > 1) {
//			Rebalance(f);
//			if (s.size()) {
//				if (f->data > s.top()->data)
//					s.top()->Rchild = f;
//				else
//					s.top()->Lchild = f;
//			}
//			else
//				root = f;
//		}
//	}
//	return 1;
//}

bool AVLtree::erase(AVLNode* &T, int x) {
	if (!T)
		return 0;
	if (T->data == x) {
		if (!T->Lchild) {
			AVLNode *p = T;
			T = T->Rchild;
			delete p;
			--count;
			return 1;
		}
		if (!T->Rchild) {
			AVLNode *p = T;
			T = T->Lchild;
			delete p;
			--count;
			return 1;
		}
		AVLNode *p = T->Lchild;
		while (p->Rchild)
			p = p->Rchild;
		T->data = p->data;
		erase(T->Lchild, T->data);
		if (T->height != max(getHeight(T->Lchild), getHeight(T->Rchild)) + 1) {
			updateHeight(T);
			if (abs(bf(T)) > 1)
				Rebalance(T);
		}
		return 1;
	}
	bool b;
	if (T->data < x)
		b = erase(T->Rchild, x);
	else
		b = erase(T->Lchild, x);
	if (b&&T->height != max(getHeight(T->Lchild), getHeight(T->Rchild)) + 1) {
		updateHeight(T);
		if (abs(bf(T)) > 1)
			Rebalance(T);
	}
	return b;
}

/*
 * int main() {
 *     AVLtree T;
 *     const int N = 5000000;
 *     set<int> is;
 *     vector<int> iv;
 *     srand(time(NULL));
 *     if (1) {
 *         for (int i = 0; i < N; ++i) {
 *             int x = rand();
 *             while (T.search(x))
 *                 x = rand();
 *             iv.push_back(x);
 *             T.insert(x);
 *         }
 *         cout << T.size() << endl;
 *         for (int i = 0; i < N; ++i)
 *             T.erase(iv[i]);
 *         cout << T.size();
 *     }
 *     else {
 *         for (int i = 0; i < N; ++i) {
 *             int x = rand();
 *             while (is.find(x)!=is.end())
 *                 x = rand();
 *             iv.push_back(i);
 *             is.insert(i);
 *         }
 *         cout << is.size() << endl;
 *         for (int i = 0; i < N; ++i)
 *             is.erase(iv[i]);
 *         cout << is.size();
 *     }
 * }
 */
