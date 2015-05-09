#include <atomic>
#include <memory>
#include <utility>


template<typename Signature>
struct Function;


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    template<typename F>
    Function(F f) :
        mImpl(new Impl<F>(std::move(f))),
        mRefCount(nullptr)
    {
    }

    Function(const Function& rhs) :
        mImpl(rhs.mImpl),
        mRefCount(rhs.mRefCount)
    {
        if (!mImpl)
        {
            return;
        }

        // refcount == nullptr means refcount is 0
        // *refcount == 0 means refcount is 1
        // *refcount == 1 means refcount is 2
        // etc...
        if (!mRefCount)
        {
            mRefCount = rhs.mRefCount = new RefCount(1); // 1 means 2
        }
        else
        {
            ++*mRefCount;
        }
    }

    Function& operator=(const Function& rhs)
    {
        Function(rhs).swap(*this);
        return *this;
    }

    Function(Function&& rhs) :
        mImpl(rhs.mImpl),
        mRefCount(rhs.mRefCount)
    {
        rhs.mImpl = nullptr;
        //rhs.mRefCount = nullptr;
    }

    Function& operator=(Function&& rhs)
    {
        Function(std::move(rhs)).swap(*this);
        return *this;
    }

    ~Function()
    {
        if (!mImpl) return;

        if (!mRefCount)
        {
        soSueMe:
            delete mImpl;
            return;
        }

        if (*mRefCount == 0) // refcount zero means one
        {
            delete mRefCount;
            mRefCount = nullptr;
            goto soSueMe;
            return;
        }

        --*mRefCount;
    }

    void swap(Function& rhs)
    {
        std::swap(mImpl, rhs.mImpl);
        std::swap(mRefCount, rhs.mRefCount);
    }

    explicit operator bool() const
    {
        return mImpl != nullptr;
    }

    template<typename ...Args2>
    R operator()(Args2&& ...a)
    {
        return mImpl->fptr_(*mImpl, std::forward<Args2>(a)...);
    }

private:
    int getRefCount() const
    {
        return mRefCount ? (*mRefCount + 1) : 0;
    }

    struct ImplBase
    {
        using FPtr = R (*)(ImplBase&, Args...);

        ImplBase(FPtr fptr) :
            fptr_(fptr)
        {
        }

        FPtr fptr_;
    };

    template<typename F>
    struct Impl : ImplBase
    {
        Impl(const F& f) :
            ImplBase([](ImplBase& base, Args ...args) { return static_cast<Impl&>(base).f_(args...); }),
            f_(f)
        {
        }

        F f_;
    };

    using RefCount = std::atomic<int>;
    using RefCountPtr = RefCount*;

    ImplBase* mImpl;
    mutable RefCountPtr mRefCount;
};


#include <iostream>


int main()
{
    {
        std::cout << '\n' << "---" << __LINE__ << std::endl;
        Function<int()> f1([]{ return 1; });
        Function<int()> f2([]{ return 2; });

        auto print = [&] {
            std::cout << "f1=" << std::flush;
            if (f1) std::cout << f1(); else std::cout << "_";
            std::cout << " f2=" << std::flush;
            if (f2) std::cout << f2(); else std::cout << "_";
            std::cout << std::endl;
        };

        print();
    }
    {
        std::cout << '\n' << "---" << __LINE__ << std::endl;
        Function<int()> f1([]{ return 1; });
        Function<int()> f2([]{ return 2; });

        auto print = [&] {
            std::cout << "f1=" << std::flush;
            if (f1) std::cout << f1(); else std::cout << "_";
            std::cout << " f2=" << std::flush;
            if (f2) std::cout << f2(); else std::cout << "_";
            std::cout << std::endl;
        };

        print();
        f1 = f2;
        f1 = f1; print();
        f2 = f2; print();
    }
    {
        std::cout << '\n' << "---" << __LINE__ << std::endl;
        Function<int()> f1([]{ return 1; });
        Function<int()> f2([]{ return 2; });

        auto print = [&] {
            std::cout << "f1=" << std::flush;
            if (f1) std::cout << f1(); else std::cout << "_";
            std::cout << " f2=" << std::flush;
            if (f2) std::cout << f2(); else std::cout << "_";
            std::cout << std::endl;
        };

        print();
        f2 = f1; print();
        f1 = f2; print();
        f1 = f1; print();
        f2 = f2; print();
    }
    {
        std::cout << '\n' << "---" << __LINE__ << std::endl;
        Function<int()> f1([]{ return 1; });
        Function<int()> f2([]{ return 2; });

        auto print = [&] {
            std::cout << "f1=" << std::flush;
            if (f1) std::cout << f1(); else std::cout << "_";
            std::cout << " f2=" << std::flush;
            if (f2) std::cout << f2(); else std::cout << "_";
            std::cout << std::endl;
        };

        print();
        f2 = std::move(f1); print();
        f1 = f2; print();
        f2 = std::move(f1); print();
        f1 = f1; print();
        f2 = f2; print();
    }
    {
        std::cout << '\n' << "---" << __LINE__ << std::endl;
        Function<int()> f1([]{ return 1; });
        Function<int()> f2([]{ return 2; });

        auto print = [&] {
            std::cout << "f1=" << std::flush;
            if (f1) std::cout << f1(); else std::cout << "_";
            std::cout << " f2=" << std::flush;
            if (f2) std::cout << f2(); else std::cout << "_";
            std::cout << std::endl;
        };

        print();
        f2 = std::move(f1); print();
        f1 = std::move(f2); print();
        f2 = f1; print();
        f1 = std::move(f2); print();
        f2 = std::move(f1); print();
        f1 = f1; print();
        f2 = f2; print();
    }
}
