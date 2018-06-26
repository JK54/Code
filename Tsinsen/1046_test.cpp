#include<iostream> 
using namespace std; 
int main () 
{ 
    char ch; 
    int sum,a; 
    cin>>sum; 
    while(true) 
    { 
	        cin>>ch; 
	        if(ch=='=') 
	            break; 
	        cin>>a; 
	        if(ch=='+') 
	            sum+=a; 
	        else sum-=a; 
	    } 
    cout<<sum<<endl; 
    return 0; 
}
