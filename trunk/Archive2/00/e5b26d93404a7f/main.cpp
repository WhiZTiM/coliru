#include <iostream>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <typeinfo>
#include <utility>

template<typename T>
struct BaseClass{
    using type = T;
};

template<typename>
struct Injector;

template<typename T, template<typename> class Base>
struct Injector<Base<T>>{
    using refined_type = std::pair<typename Base<T>::type, typename Base<T>::type>;
    Base<refined_type> refined_storage;
};

int main() {
    Injector<BaseClass<int>> injector;
	
	return 0;
}
