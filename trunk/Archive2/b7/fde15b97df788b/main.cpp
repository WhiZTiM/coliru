#include <iostream>
#include <functional>
#include <string>
using namespace std;


class FunctionPointer
{
    void* fp;
public:
	FunctionPointer(void* ptr)
	: fp(ptr)
	{}
	
	// Overload casting operator to 
	// a certain function signiture
	template<class R, class... ARGS>
	operator std::function<R(ARGS...)> (){
        typedef R(*func_ptr)(ARGS...);
        return std::function<R(ARGS...)>((func_ptr)fp);
	}
};

void hello(string msg){
	cout << "Hello " << msg << endl;
}

int main() {
	
	FunctionPointer f((void*)hello);
	
	function<void(string)> func_hello = f;
	
	func_hello("World!");
	
	return 0;
}