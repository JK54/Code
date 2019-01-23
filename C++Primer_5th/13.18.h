#include "comm.h"

class Employee
{
	public:
		Employee():Name("null"),ID(unique_id++){}
		Employee(const std::string & name):Name(name),ID(unique_id++){}
		Employee& operator=(const Employee&) = delete;
		std::string getName(){return Name;}
		int getID(){return ID;}
	private:
		std::string Name;
		int ID;
		static int unique_id;
};

int Employee::unique_id = 0;
