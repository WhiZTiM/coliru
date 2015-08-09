#include <tuple>

namespace my_project {
    template< typename >
    void get() = delete;

    std::tuple< int > blah;
    int q = get< 0 >( blah );
}

int main() {}