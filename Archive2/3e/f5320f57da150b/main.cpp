// clang++ -std=c++1y -O3 -DNDEBUG -pedantic -Wall -lboost_timer -lboost_system main.cpp

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/timer/timer.hpp>

#include <type_traits>
#include <iostream>
#include <utility>
#include <cstddef>
#include <vector>

using namespace std;

/****************************************************************/
template<size_t Size>
class Freelist
{
    union Chunk
    {
        aligned_storage_t<Size> storage;
        Chunk *next;
    };
    vector<vector<Chunk>> chunks;
    size_t total_count = 0u;
    Chunk *head = nullptr;

    Chunk *add_chunks(size_t count, Chunk *tail = nullptr)
    {
        chunks.emplace_back(count);
        for(auto &chunk : chunks.back())
        {
            chunk.next = tail;
            tail = &chunk;
        }
        total_count += count;
        return tail;
    }

public:
    Freelist(size_t count = 128)
        : head(add_chunks(count))
    {}

    Freelist(const Freelist&) = delete;
    Freelist &operator=(const Freelist&) = delete;

    void *allocate()
    {
        if(head == nullptr)
            head = add_chunks(total_count + 1);

        auto result = head;
        head = head->next;
        return result;
    }

    void deallocate(void *p)
    {
        auto chunk = static_cast<Chunk*>(p);
        chunk->next = head;
        head = chunk;
    }
};

template<size_t Size>
struct Allocator
{
    static Freelist<Size> value;
};

template<size_t Size>
Freelist<Size> Allocator<Size>::value{};

/****************************************************************/
class any
{
    class interface
    {
        size_t reference_count = 0;

        friend void intrusive_ptr_add_ref(interface *p)
        {
            ++p->reference_count;
        }
        friend void intrusive_ptr_release(interface *p)
        {
            if(--p->reference_count == 0)
                p->release();
        }

    public:
        virtual any operator()(any) const = 0;
        virtual void release() = 0;

    protected:
        ~interface(){}
    };

    template<typename F>
    class concrete : public interface
    {
        F f;

    public:
        concrete(F x) noexcept(noexcept(F{move(x)}))
          : f(move(x))
        {}

        any operator()(any x) const override
        {
            return f(move(x));
        }

        void release() override
        {
            this->~concrete();
            Allocator<sizeof(concrete)>::value.deallocate(this);
        }
    };

    boost::intrusive_ptr<interface> shared_interface;

public:
    template<typename F>
    any(F f)
        : shared_interface
          {
              new ( Allocator<sizeof(concrete<F>)>::value.allocate() )
                  concrete<F>{move(f)}
          }
    {
        static_assert(noexcept(concrete<F>{move(f)}), "");
    }

    any operator()(any x) const
    {
        return (*shared_interface)(move(x));
    }
};

/****************************************************************/

auto zero = [](auto) { return [](auto z) { return z; }; };

auto succ = [](auto n)
{
    return [n=move(n)](auto s)
    {
        return [=, s=move(s)](auto z)
        {
            return s(n(s)(move(z)));
        };
    };
};

any /* <--- erased type */ power = [](auto b)
{
    return [b=move(b)](const auto &e)
    {
        return e(b);
    };
};

template<size_t N> auto n() { return succ(n<N-1>()); }
template<> auto n<0>() { return zero; }

int main()
{
    auto result = 0;
    auto action = [&](auto) { ++result; return zero; };
    {
        boost::timer::auto_cpu_timer t;
        any /* <--- erased type */ num = n<9>();
        power(num)(num)(action)(zero);
    }
    cout << result << endl;
}
