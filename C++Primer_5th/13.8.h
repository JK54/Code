#include "comm.h"

class HasPtr
{
	public:
		HasPtr(const std::string &s = std::string()):ps(std::make_shared<std::string>(s)),i(0){}
		HasPtr(const HasPtr &orig):ps(orig.ps),i(orig.i){}
		HasPtr& operator=(const HasPtr& sot)
		{
			std::shared_ptr<std::string> ps(sot.ps);
			i = sot.i;
			return *this;
		}
		~HasPtr(){}
	private:
		std::shared_ptr<std::string> ps;
		int i;
};
