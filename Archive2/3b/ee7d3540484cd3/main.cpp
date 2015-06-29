// clang++ -std=c++1y -O3 -DNDEBUG -pedantic -Wall -lboost_timer -lboost_system main.cpp

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/timer/timer.hpp>

#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <cstddef>
#include <vector>

using namespace std;

/****************************************************************/
template<size_t Size>
class free_list_pool
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
    free_list_pool(size_t count = 128)
        : head(add_chunks(count))
    {}

    free_list_pool(const free_list_pool&) = delete;
    free_list_pool &operator=(const free_list_pool&) = delete;

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
struct fast_allocator
{
    static free_list_pool<Size> value;
};

template<size_t Size>
free_list_pool<Size> fast_allocator<Size>::value{};

template<typename T, typename ...Args>
boost::intrusive_ptr<T> make_intrusive(Args&&... args)
{
    static_assert(noexcept(T{forward<Args>(args)...}), "");

    return new (fast_allocator<sizeof(T)>::value.allocate()) T{forward<Args>(args)...};
}

template<typename T>
void release_intrusive(T *p)
{
    p->~T();
    fast_allocator<sizeof(T)>::value.deallocate(p);
}

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
        virtual any operator()(any) const
        {
            throw domain_error("is not any(any)");
        }

        virtual operator int() const
        {
            throw domain_error("is not int");
        }

        virtual void release() = 0;

    protected:
        ~interface(){}
    };

    template<typename Derived>
    class interface_with_release : public interface
    {
        void release() override
        {
            release_intrusive<Derived>(static_cast<Derived *>(this));
        }
    };

    template<typename F>
    class concrete_function : public interface_with_release<concrete_function<F>>
    {
        F f;

    public:
        concrete_function(F x) noexcept(noexcept(F{move(x)}))
          : f(move(x))
        {}

        any operator()(any x) const override
        {
            return f(move(x));
        }
    };

    class concrete_int : public interface_with_release<concrete_int>
    {
        int i;

    public:
        concrete_int(int x) noexcept
            : i(x)
        {}

        operator int() const override
        {
            return i;
        }
    };

    boost::intrusive_ptr<interface> shared_interface;

public:
    template<typename F>
    any(F f)
        : shared_interface{ make_intrusive<concrete_function<F>>(move(f)) }
    {}

    any(int x)
        : shared_interface{ make_intrusive<concrete_int>(x) }
    {}

    any operator()(any x) const
    {
        return (*shared_interface)(move(x));
    }

    operator int() const
    {
        return *shared_interface;
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

any /* <--- erased type */ inc = [](auto x)
{
    return x + 1;
};

template<size_t N> auto n() { return succ(n<N-1>()); }
template<> auto n<0>() { return zero; }

int main()
{
    auto result = 0;
    {
        boost::timer::auto_cpu_timer t;
        any /* <--- erased type */ num = n<9>();
        result = power(num)(num)(inc)(0);
    }
    cout << result << endl;
}
