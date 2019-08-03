#include <iostream>
#include <mutex>
#include "SingletonPattern.h"

Singleton::Singleton(){}

Singleton* Singleton::GetInstance()
{
	//使用时才初始化
	if(Instance == nullptr)
	{
		//双检锁DCL
		std::lock_guard<std::mutex> lock(mmtex);//自解锁。析构时解锁。
		if(Instance == nullptr)
			Instance = new Singleton;
	}
	return Instance;
}

void Singleton::example()
{
	std::cout<<"This is a test."<<std::endl;
}

Singleton::GC::~GC()
{
	if(Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
	std::cout<<"destory."<<std::endl;
}
