#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string
#include <chrono>

class Generic
{
public:
    template<typename T> Generic& operator<<(const T& v)
    {
    	handleData(v);
    	return *this;
    }
protected:
	template<typename T> void handleData(const T& v)
	{
		std::cout << "Generic Handle Data: " << v << std::endl;
	}
};

class Dummy
{
public:
    Dummy(int v) : _v(v)
	{
		std::cout << "InitDummy with " << v << std::endl;
	}
	int getVal() const
	{
		return _v;
	}
private:
	int _v;
};

class Specific : public Generic
{
public:
    /*template<typename T> Specific& operator<<(const T& v)
    {
        handleData(v);
    	return *this;
    }*/

protected:
    void handleData(const Dummy& v)
    {
        Generic::handleData(v.getVal());
    }
};

int main () {
    Specific g;
    
    g << 5 << "hello" << Dummy(666);
    return 0;
}
