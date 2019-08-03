#ifndef _SINGELTON_
#define _SINGELTON_
#include <mutex>

class Singleton
{
	public:
		static Singleton* GetInstance();
		void example();
	private:
		//私有的默认构造函数
		Singleton();
		//不定义防止编译器生成默认的拷贝构造函数与赋值运算符
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
	private:
		//唯一实例
		static Singleton *Instance;
		//自解锁
		static std::mutex mmtex;
		//垃圾回收
		class GC
		{
			public:
				~GC();
			public:
				static GC gc;
		};
};

#endif
