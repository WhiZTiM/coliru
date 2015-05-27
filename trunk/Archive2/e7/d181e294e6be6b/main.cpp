#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <string>
 
template<typename... Args>
using void_t = void;
 
template<typename T, typename = void>
    	struct is_iterator : std::false_type {
 
		};
 
		template<typename T>
		struct is_iterator<T, void_t<typename std::iterator_traits<T>::value_type>> : std::true_type {
 
		};
 
int main() {
	std::cout << std::boolalpha
        << " " << is_iterator<int*>::value << "\n"
        << " " << is_iterator<int>::value << "\n"
        << " " << is_iterator<std::string::iterator>::value << "\n"
        << " " << is_iterator<std::back_insert_iterator<std::vector<int>>>::value;
}