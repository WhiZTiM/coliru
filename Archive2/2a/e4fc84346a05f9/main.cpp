#include <iostream>

namespace test {

template<class T>
class Base {
public:
    Base();
	virtual ~Base();
};

}


namespace test {

template<class T>
Base<T>::Base() {
    // TODO Auto-generated constructor stub

}

template<class T>
Base<T>::~Base() {
	// TODO Auto-generated destructor stub
}

}

namespace test {

class Derived : public Base<int> {
public:
    Derived();
	virtual ~Derived();
};

} /* namespace aeirtuaccess */

namespace test {

Derived::Derived() {
    // TODO Auto-generated constructor stub

}

Derived::~Derived() {
	// TODO Auto-generated destructor stub
}

}

int main()
{
    test::Derived d;
    std::cout << "OK" << std::endl;
}
