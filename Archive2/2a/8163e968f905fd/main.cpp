#define BOOST_NO_ASSERT

#include <boost/coroutine/all.hpp>
#include <exception>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

template<unsigned N>
struct coroutine_stack
{
    static constexpr auto size = N;
    char buf[N];

    auto allocator()
    {
        struct
        {
            void *stack_top;

            void allocate(coroutines::stack_context &sctx, size_t s)
            {
                if(s > N) throw bad_alloc{};
                sctx.size = N;
                sctx.sp = stack_top;
            }
            void deallocate(coroutines::stack_context &) const {}
        } res = {buf + N};
        return res;
    }
};

unsigned long counter = 0;

int main() try
{
    struct Fiber
    {
        coroutine_stack<256> stack;
        coroutines::symmetric_coroutine<void>::call_type coro;
        
        Fiber()
            :   coro{[](auto &yield)
                {
                    while(true)
                    {
                        ++counter;
                        yield();
                    }
                }, coroutines::attributes(stack.size), stack.allocator()}
        {}
    };
    
    vector<Fiber> fibers(3.5e6);
    cout << fibers.size() << " coroutines;"
         << " allocated for stacks+coroutines: "
         << sizeof(fibers.front()) * fibers.size() / (1u << 20)
         << "MiB" << endl;

    while(true)
    {
        for(auto &fiber : fibers)
            fiber.coro();
        cout << counter << endl;
    }
}
catch(const std::exception &e)
{
    cout << e.what() << endl;
}
