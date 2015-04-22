#include <algorithm>
#include <functional>

#include <iostream>

// Dummy
template <typename C, typename F>
void parallel_for_each( C&& c, F&& f ) {
    using std::begin; using std::end;
    std::for_each(begin(c), end(c), std::forward<F>(f));
}

template <typename Container>
struct Helper {
    Container&& c;
    template <typename Arg>
    void operator=(Arg&& arg) {
        parallel_for_each(std::forward<Container>(c), std::forward<Arg>(arg));
    }
};

#define CONCAT_(a,b) a##b
#define CONCAT(a,b) CONCAT_(a,b)
// Easier with Boost.PP
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC(i) CONCAT(DEC_,i)

#define pforeach(Z, ...) \
  Helper<decltype((__VA_ARGS__))> CONCAT(_unused_obj, __COUNTER__){__VA_ARGS__}; \
  CONCAT(_unused_obj, DEC(__COUNTER__))=[](Z)

int main()
{
    int a[] = {1, 2, 3};
    pforeach(int i, a) {
        std::cout << i << ", ";
    };
    pforeach(int i, std::vector<int>{1, 2, 3}) {
        std::cout << -i << ", ";
    };
}
