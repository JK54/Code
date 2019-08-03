#include "SingletonPattern.h"
#include <iostream>
#include <mutex>

//懒汉式，第一次使用才初始化。
Singleton *Singleton::Instance = nullptr; 
std::mutex Singleton::mmtex;
Singleton::GC Singleton::GC::gc;

int main()
{
	Singleton *p = Singleton::GetInstance();
	p->example();
	return 0;
}
