#include <iostream>
#include <tuple>
#include <functional>
using namespace std;

template<typename OP, typename F1, typename... Fs>
struct symop {
     OP op;
     tuple<F1,Fs...> fs;

     symop(const OP &oopp, const F1 &f1, const Fs &...ffss)
          : op(oopp), fs(f1,ffss...) {}
};

template<typename OP, typename... Fs>
auto baz(const symop<OP,Fs...> &so) {
     return so.op(get<0>(so.fs),get<1>(so.fs));
}

/* // this version compiles on both compilers
template<typename OP, typename F1, typename... Fs>
auto baz(const symop<OP,F1,Fs...> &so) {
     return so.op(get<0>(so.fs),get<1>(so.fs));
}
*/

int main() {
     symop<plus<int>,int,int> so{plus<int>{},3,4};
     cout << baz(so) << endl;
}
