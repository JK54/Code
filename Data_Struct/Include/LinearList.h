#ifndef _LINEAR_H
#define _LINEAR_H

#include "sys_comm.h"

template <typename T>
class LinearList
{
	public:
		LinearList() = default;
		~LinearList() = default;
	protected:
		virtual int size() const = 0;
		virtual int length() const = 0;
		virtual int search(T&) const = 0;
		// virtual int locate(int i) const = 0;
		virtual bool getdata(int i ,T &x) const = 0;
		virtual void setdata(int i,T &x) = 0;
		virtual bool insert(int i ,T &x) = 0;
		virtual bool remove(int i ,T&x) = 0;
		virtual bool isempty() const = 0;
		virtual bool isfull() const = 0;
		virtual void sort() = 0;
		virtual void input() = 0;
		virtual void output()  = 0;
		// LinearList<T> operator=(LinearList<T> &L) = 0;
};

#endif
