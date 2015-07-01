#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <set>
using namespace std; // Don't do this at work


// Mocking classes
struct A {  
};
template<typename T>
struct Comparator {
    bool operator()(const T& a, const T& b) const {
        return true;
    }
};
template<class Value> class MapToValue {
     template<class Key, class Allocator = std::allocator<std::pair<const Key, Value>>> 
     struct FromKey : public std::map<Key, Value, Comparator<Key>, 
     Allocator> {};
};
// End of mocking classes

template< template<class T, class Allocator = std::allocator<T>> class Container > Container<std::weak_ptr<A>>* Foo() {
    cout << "first" << endl;
    return new Container<std::weak_ptr<A>>();
}

template< template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T>> class Container > Container<std::weak_ptr<A>>* Foo() {
    cout << "second" << endl;
    return new Container<std::weak_ptr<A>>();
}

template< template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> >> class Container > 
Container<std::weak_ptr<A>, int>* Foo() {
    cout << "third" << endl;
    return new Container<std::weak_ptr<A>, int>();
}

int main() {
  Foo<std::vector>();
  Foo<std::set>();
  Foo<std::map>();
}