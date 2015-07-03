#include <utility>
#include <vector>
using namespace std;

template< class T >
T&& my_forward( typename std::remove_reference<T>::type& t )
{
    return static_cast<T&&>(t);
}

class Library
{
    vector<int> b;
public:
    // hi! only rvalue here :)
    Library( vector<int>&& a):b(std::move(a)){

    }
};

int main() 
{
    vector<int> v;
    v.push_back(1);
    Library a( my_forward<vector<int>>(v));
    return 0;
}