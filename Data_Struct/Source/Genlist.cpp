#include "../Include/GenList.h"

template<typename T>
GenList<T>::GenList()
{
	first = new GenListNode<T>();
	if(first == nullptr)
		std::cout<<"init failed!"<<std::endl;
}

template<typename T>
void Remove(GenListNode<T> *ls,T x)
{
	if(ls->tlink != nullptr)
	{
		GenListNode<T> *q = ls->tlink;
		while(q != nullptr && (q->utype == 1 && q->info.value == x))
		{
			ls->tlink = q->tlink;
			delete q;
			std::cout<<"Removing..."<<std::endl;
			q = ls->tlink;
		}
		if(q != nullptr)
		{
			if(q->utype == 2)
				Remove(q->info.hlink,x);
			Remove(q,x);//q->info.value != x,从q开始往后再递归进行判断
		}
	}
}

template<typename T>
void GenList<T>::Remove(GenListNode<T> *ls)
{
	ls->info.ref--;
	if(ls->info.ref <= 0)	
	{
		GenListNode<T> *p;
		while(ls->tlink != nullptr)
		{
			p = ls->tlink;
			if(p->utype == 2)
			{
				std::cout<<"Removing chid.."<<std::endl;
				Remove(p->info.hlink);
				if(p->info.hlink->info.ref <= 0)
					delete p->info.hlink;
			}
			ls->tlink = p->tlink;
			delete p;
		}
	}
}

template<typename T>
GenList<T>::~GenList()
{
	Remove(first);
}

template<typename T>
bool Equal(GenListNode<T> *l,GenListNode<T> *r)
{
	bool recur;
	GenListNode<T> *p,*q;
	if(l->tlink == nullptr && r->tlink == nullptr)
	{
		std::cout<<"Two empty genlist equal.."<<std::endl;
		return true;
	}
	if(l->tlink != nullptr && r->tlink != nullptr && l->tlink->utype == r->tlink->utype)
	{
		if(l->tlink->utype == 1)
			recur = l->tlink->info.value == r->tlink->info.value?true:false;
		else if (l->tlink->utype == 2)
			recur = Equal(l->tlink->info.hlink,r->tlink->info.hlink);
		if(recur == true)
			return Equal(l->tlink,r->tlink);
	}
	return false;
}

template<typename T>
GenListNode<T> *Next(const GenListNode<T> &elem)
{
	if(elem->tlink == nullptr)
		return nullptr;
	else
		return elem->tlink;
}

template<typename T>
GenListNode<T>* GenList<T>::First()
{
	if(first == nullptr)
		return nullptr;
	else
		return first;
}

template<typename T>
GenListNode<T>* GenList<T>::Copy( GenListNode<T> &ls)
{
	GenListNode<T> *p = nullptr;
	if(ls != nullptr)
	{
		p = new GenListNode<T>;
		p->utype = ls->utype;
		switch(ls->utype)
		{
			case 0:
				p->info.ref = ls->info.ref;
				break;
			case 1:
				p->info.value = ls->info.value;
				break;
			case 2:
				p->info.hlink = Copy(ls->info.hlink);
				break;
		}
		p->tlink = Copy(ls->tlink);
	}
	return p;
}

template<typename T>
bool GenList<T>::Copy(const GenList<T> &s)
{
	first = Copy(s.first);
	if(first != nullptr)
		return true;
	else
	{
		std::cout<<"copy failed.."<<std::endl;
		return false;
	}
}
template<typename T>
void Createlist(GenListNode<T> *ls,std::istream &is)
{
	size_t utype;
	T value;
	GenListNode<T> *p = new GenListNode<T>;
	GenListNode<T> *pre;
	ls->tlink = p;
	while(is)
	{
		// std::cout<<"input the utype value,99 for end,1 for value node,2 for list node"<<std::endl;
		is>>utype;
		switch(utype)
		{
			case 99:
				pre->tlink = nullptr;
				delete p;
				return;
			case 1:
				// std::cout<<"input the value(be care of value type)"<<std::endl;
				is>>value;
				p->utype = utype;
				p->info.value = value;
				break;
			case 2:
				p->utype = utype;
				std::cout<<"you are creating child list"<<std::endl;
				GenListNode<T> *q = new GenListNode<T>;
				q->utype = 0;
				p->info.hlink = q;
				Createlist(q,is);
				std::cout<<"chid list created"<<std::endl;
				break;
		}
		p->tlink = new GenListNode<T>;
		pre = p;
		p = p->tlink;
	}
}

template<typename T>
void Traverse(GenListNode<T> *ls)
{
	if(ls->tlink == nullptr)
	{
		std::cout<<"It's a empty list"<<std::endl;
		return;
	}
	GenListNode<T> *p = ls->tlink;
	while (p != nullptr)
	{
		if(p->utype == 1)
			std::cout<<p->info.value<<" ";
		if(p->utype == 2)
		{
			std::cout<<p->info.value;
			std::cout<<"( ";
			Traverse(p->info.hlink);
			std::cout<<") ";
		}
		p = p->tlink;
	}
}

template<typename T>
size_t GenList<T>::depth(GenListNode<T> *ls)
{
	size_t m = 0,n;
	GenListNode<T> *p;
	if(ls->tlink == nullptr)
	{
		return 1;
	}
	p = ls->tlink;
	while(p->tlink != nullptr)
	{
		if(p->utype == 2)
		{
			n = depth(p->info.hlink);
			if(m<n)
				m = n;
		}
		p = p->tlink;
	}
	return m + 1;

}

template<typename T>
size_t GenList<T>::Depth()
{
	return depth(first);
}

template<typename T>
/*想到的方法：
 * 1、用一个vector保存每次遇到子列时的长度值，遍历完成sort以后直接返回最大值即可，最简单，但是效率略低
 * 2、只使用一个变量，每次比较遇到子列时的值，保存较大的那个。
 * 果然有时候把思路写下来会更好实现一些，没写注释以前第2种方法思考了十几分钟，写了以后马上就想到了
 */
size_t GenList<T>::length(GenListNode<T> *ls)
{
	if(ls->tlink == nullptr)
		return 0;
	size_t m = 0,n,cn = 0;
	GenListNode<T> *p = ls->tlink;
	while(p != nullptr)
	{
		if(p->utype == 2)
		{
			n = length(p->info.hlink);
			cn = cn > m + n + 1?cn:m + n + 1;
			std::cout<<"cn : "<<cn<<std::endl;
		}
		// if(p->utype != 2)
		// utype = 2的点按道理也应该算到长度里面
		p = p->tlink;
		++m;
		std::cout<< m << " ";
	}
	m = m > cn ? m : cn;
	return m;
}

template<typename T>
size_t GenList<T>::Length()
{
	return length(first);
}
