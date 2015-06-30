
#include <iostream>

class Base1{};
class Base2{};


template<class T>
class Derived : public T {


public:
    Derived();

};

template<class T>
Derived<T>::Derived()
{
    std::cout << "Hello from derived!\n";
}

int main()
{

	Derived<Base1> dB1;
	Derived<Base2> dB2;
}