#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string
#include <chrono>
#include <type_traits>
#include <typeindex>

#define ONLY_ARITHMETIC typename std::enable_if<std::is_arithmetic<T>::value, int>::type U=0

template <class B>
class Generic
{
public:
    template<typename T> Generic& operator<<(const T& v)
    {
        handleData(v);
    	return *this;
    }
protected:
	template<typename T, ONLY_ARITHMETIC> void handleData(const T& v)
	{
        std::cout << "Handling type: " << std::type_index(typeid(v)).name() << std::endl;
	}
    template<typename T> void handleData(const std::vector<T>& v)
    {
        T dummy;
        std::cout << "Handling vector of type: " << std::type_index(typeid(dummy)).name() << std::endl;
        for(const auto& vv : v)
        {
            static_cast<B*>(this)->handleData(vv);
        }
        std::cout << "End of vector" << std::endl;
    }
};

class Dummy
{
public:
    Dummy() {};
    Dummy(int v) : _v(v)
	{
	}
	int getVal() const
	{
		return _v;
	}
private:
	int _v;
};

class DummyArray
{
public:
    DummyArray(std::vector<Dummy> v) : _v(v)
    {
	}
	std::vector<Dummy> getVal() const
	{
		return _v;
	}
private:
	std::vector<Dummy> _v;
};


class Specific : public Generic<Specific>
{
public:
    template<typename T> Specific& operator<<(const T& v)
    {
        handleData(v);
    	return *this;
    }

public:
    void handleData(const Dummy& v)
    {
        Generic::handleData(v.getVal());
    }
    void handleData(const DummyArray& v)
    {
        Generic::handleData(v.getVal());
    }
    
    using Generic::handleData;
};

int main () {
    Specific g;
    
    //g << 5 << std::vector<int>({1, 2, 3}) << Dummy(666);
    g << 5 << std::vector<int>({1, 2, 3}) << Dummy(666) << DummyArray({Dummy(123)});
    
    return 0;
}
