#include <iostream>
#include <type_traits>
using namespace std;

int main() 
{
    cout<<boolalpha;
    typedef char* charp;
	cout<<is_same<charp, char*>::value<<endl;
	cout<<is_same<const charp,  char*const>::value<<endl;
	
	return 0;
}
