#include <boost/bind.hpp>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <new>
#include <utility>
#include <array>


template<typename Signature>
struct Function;


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    Function() : mStorage() {}

    template<typename F>
    Function(F f)
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(Impl<F>) <= sizeof(mStorage), "");
        new (mStorage.data()) Impl<F>(std::move(f)); 
    }

    Function(const Function& rhs) : mStorage()
    {
        if (rhs.valid())
        {
            rhs.base().copy_to(data());
        }
    }

    Function& operator=(const Function& rhs)
    {
        if (this == &rhs)
        {
            return *this; 
        }
        
        if (valid())
        {
            base().~Base();
            mStorage.unset();
        }
        
        if (rhs.valid())
        {
            rhs.base().copy_to(*this);
        }
        
        return *this;
    }

    Function(Function&& rhs) noexcept :
        mStorage(rhs.mStorage)
    {
        if (rhs.valid())
        {
            rhs.move_to(*this);
        }
    }

    Function& operator=(Function&& rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this; 
        }
        
        if (valid())
        {
            base().~Base();
            mStorage.unset();
        }
        
        if (rhs.valid())
        {
            rhs.base().move_to(*this);
            rhs.mStorage.unset();
        }
        return *this;
    }

    ~Function()
    {
        if (valid())
        {
            base().~Base();
        }
    }

    explicit operator bool() const
    {
        return valid();
    }

    R operator()(Args&& ...args) const
    {
        if (!valid())
        {
            throw std::bad_function_call();
        }
        return base().call(std::forward<Args>(args)...);
    }

private:
    void move_to(Function& dst)
    {
        if (dst.valid()) dst.base().~Base();
        base().move_to(dst.data());
        mStorage = Storage();
    }
    
    struct Base;
    
    const Base& base() const { return static_cast<const Base&>(static_cast<const NonPolymporphicBase&>(mStorage)); }
    Base& base() { return static_cast<Base&>(static_cast<NonPolymporphicBase&>(mStorage)); }
    
    bool valid() const { return mStorage.mData[0] != 0; }

    const void* data() const { return static_cast<const void*>(mStorage.data()); }
    void* data() { return static_cast<void*>(mStorage.data()); }
    
    // This helper base allows us to reinterpret from
    // Storage* to Base* without triggering aliasing warnings.
    struct NonPolymporphicBase {};
    
    struct Base : NonPolymporphicBase
    {
        virtual ~Base() {}
        virtual R call(Args ...args) const = 0;
        virtual void copy_to(void* where) const = 0;
        virtual void move_to(void* where) = 0;
    };

    template<typename F>
    struct Impl final : Base
    {
        Impl(F&& f) : f(std::move(f)) {}
        R call(Args ...args) const { return f(args...); }
        void copy_to(void* where) const { new (where) Impl<F>(*this); }
        void move_to(void* where) { new (where) Impl<F>(std::move(*this)); }
        F f;
    };

    struct Storage : NonPolymporphicBase
    {
        const void* data() const { return mData.data(); }
        void* data() { return mData.data(); }
        void unset() { mData[0] = 0; }
        std::array<long, 3> mData;
    };
    
    static_assert(std::is_pod<Storage>::value, "");    
    Storage mStorage;
};


int main()
{
    long a = 1, b = 2, c = 3;
    Function<void()> ff = [&]() {
        a = 0, b = 0;
    };
    ff();
    
    a++; ff(); 
    b++; ff(); 
    c++; ff(); 
    
    
    Function<void(int&)> inc = [](int& n) { n += 1; };
    int n = 3;
    inc(n);
    assert(n == 4);
    std::cout << "n=" << n << std::endl;
}
