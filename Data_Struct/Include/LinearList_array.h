#ifndef _LINEAR_ARR_H
#define _LINEAR_ARR_H

#include "LinearList.h"

template <typename T>
class LinearList_array : public LinearList<T>
{
	public:
		LinearList_array() = default;
		LinearList_array(size_t sz);
		~LinearList_array();
		virtual int size() const override;
		virtual int length() const override;
		virtual int search(T &) const override;
		virtual bool getdata(int i,T &x) const override;
		virtual void setdata(int i,T &x) override;
		virtual bool insert(int i, T &x) override;
		virtual bool remove(int i ,T &x) override;
		virtual bool isempty() const override;
		virtual bool isfull() const override;
		virtual void sort() override;
		virtual void input() override;
		virtual void output() override;
		// LinearList_array<T> operator=(LinearList_array<T> &L);
	private:
		T *data;
		size_t maxsize;
		size_t last;
		void resize(size_t newsize);
		void resize();
		void free();

};

#endif
