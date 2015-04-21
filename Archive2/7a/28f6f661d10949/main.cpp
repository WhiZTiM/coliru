#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp> 

using namespace std;

template<typename T>
void f(T t) {
    cout << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name()  << endl;
}

int main(int, char*[]) {
    f(1 == 0);
    f(0);
    f(0L);
    f(NULL);
    f(nullptr);
    return 0;
}