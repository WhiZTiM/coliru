#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <thread>
#include <mutex>
using namespace std;
 
struct Foo {
private:
    int _i = 0;
	mutable std::mutex _mutex;
public:
	int f() const
	{
		std::lock_guard<std::mutex> locker(_mutex);
		return _i;
	}
 
};
 
int main()
{
	Foo foo;
	foo.f();
    std::cout << "Lock Succeded!" << std::endl;
	return 0;
}