#include <boost/heap/fibonacci_heap.hpp>
#include <boost/tuple/tuple_comparison.hpp>

struct W {
    int a;
    int b;
    
    W(int a, int b) : a(a), b(b) { }

    boost::tuple<int const&, int const&> get_key() const { return boost::tie(a, b); }

    void decr() { b?a:--a, b?--b:b; }
};

struct heap_data;
using Heap = boost::heap::fibonacci_heap<heap_data>;

struct heap_data
{
    W payload;
    Heap::handle_type handle;

    heap_data(W w) : payload(w), handle() {}

    bool operator<(heap_data const & rhs) const {
        return payload.get_key() < rhs.payload.get_key();
    }
};

#include <vector>
#include <iostream>

int main()
{
    Heap heap;

    std::vector<Heap::handle_type> handles;

    for (int i = 0; i < 10; i++)
    {
        auto h = heap.push(W { i, i + 3 });
        handles.push_back(h);
        (*h).handle = h;
    }

    (*handles[5]).payload.decr();
    heap.decrease(handles[5]);
}
