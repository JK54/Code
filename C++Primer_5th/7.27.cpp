#include "chapter7.h"

int main()
{
		Screen myScreen(5,5,'X');
		myScreen.move(4,0).set('#').display(cout);
		cout<<endl;
		myScreen.display(cout);
		cout<<endl;
		return 0;
}
