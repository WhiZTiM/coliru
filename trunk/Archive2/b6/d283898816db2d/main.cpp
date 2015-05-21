#include <iostream>
#include <memory>
using namespace std;

struct list_impl {
    int head;
    unique_ptr<list_impl> tail;
};

using List = unique_ptr<struct list_impl>;
List cons(int head, List tail) { return make_unique<list_impl>(head, tail); }
List nil() { return {}; }

int main() {
    auto const l = cons(1, cons(2, cons(3, nil())));
    
    auto const recursor = [&](auto x, auto rec){
        cout << x->head << ' ';
        if(x->tail) {
            rec(x->tail, rec);
        }
    };
    
    recursor(l, recursor);
}
