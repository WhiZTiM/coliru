#include <type_traits>
#include <future>
#include <memory>
#include <iostream>
#include <utility>


//! SetPromise is a utility function for setting a non-void promise.
template<typename R, typename F, typename ...Args>
void SetPromise(std::promise<R>& p, F&& f, Args&& ...args)
{
    try
    {
        p.set_value(f(std::forward<Args>(args)...));
    }
    catch (...)
    {
        p.set_exception(std::current_exception());
    }
}


//! SetPromise overload for promise<void>.
template<typename F, typename ...Args>
void SetPromise(std::promise<void>& p, F&& f, Args&& ...args)
{
    try
    {
        f(std::forward<Args>(args)...);
        p.set_value();
    }
    catch (...)
    {
        p.set_exception(std::current_exception());
    }
}


struct Internal {};


//! ImplBase is the base for the "Impl"-object stored inside DispatchTask.
//! It does not have virtual methods. A function pointer is used for dynamic
//! dispatch to the run method.
//! Because we don't have a virtual destructor the derived object should be
//! created as a shared_ptr<Derived>, which is calls the right destructor
//! and which is implicitly convertible to shared_ptr<ImplBase>. This
//! frees the DispatchTask from the burden of correct cleanup.
struct ImplBase
{
    // function pointer to the implementation
    using FPtr = void (*) (Internal, ImplBase&);

    // FPtr is a function pointer to the real run function.
    // It must be passed here by the constructor of the derived object.
    // Note that a stateless lambda can be used for this (since they
    // are convertible to function pointer).
    ImplBase(FPtr fptr) : fptr_(fptr)
    {
        // This object should not have virtual methods.
        // This static assert was added emphasize that.
        static_assert(!std::is_polymorphic<ImplBase>::value, "");
    }

    void run(Internal in)
    {
        fptr_(in, *this);
    }

    FPtr fptr_;
};


//! SimpleImpl is a simple task without future/promise overhead
template<typename F>
struct SimpleImpl : ImplBase
{
    // F is typically a lambda, but can be any callable object.
    SimpleImpl(F f) :
        ImplBase([](Internal in, ImplBase& base){
            static_cast<SimpleImpl&>(base).run(in);
        }),
        f_(std::move(f))
    {}

    void run(Internal in)
    {
        f_(in);
    }

    F f_;
};


// Creating a SimpleImpl<F> object requires us to know the type of
// the passed function object. If a lambda is used then we need this
// helper function to deduce its type.
template<typename F>
std::shared_ptr<SimpleImpl<F>> MakeImpl(const F& f)
{
    return std::make_shared<SimpleImpl<F>>(f);
}


//! ImplWithFuture bundles the task with future and promise.
template<typename F>
struct ImplWithFuture : ImplBase
{
    // F is typically a lambda, but can be any callable object.
    ImplWithFuture(F f) :
        ImplBase([](Internal in, ImplBase& base){ static_cast<ImplWithFuture&>(base).run(in); }),
        f_(std::move(f))
    {
    }

    void run(Internal in)
    {
        SetPromise(prom_, f_, in);
    }
    
    
    using R = decltype(std::declval<F>()(std::declval<Internal>()));

    std::future<R> get_future() { return prom_.get_future(); }

    F f_;
    std::promise<R> prom_;
};


// Creating a ImplWithFuture<F> object requires us to know the type of
// the passed function object. If a lambda is used then we need this
// helper function to deduce its type.
template<typename F>
std::shared_ptr<ImplWithFuture<F>> MakeImplWithFuture(const F& f)
{
    return std::make_shared<ImplWithFuture<F>>(f);
}


//! DispatchTask is a type-erased (non-templated) function object.
//! It is the object passed to the task queue.
struct DispatchTask
{
    // The Impl must be created as a shared_ptr in order to
    // ensure the most derived destructor will be called later.
    template<typename Impl>
    DispatchTask(std::shared_ptr<Impl>&& ptr) : mImpl(std::move(ptr))
    {
    }

    void operator()(Internal in) const
    {
        mImpl->run(in);
    }

    std::shared_ptr<ImplBase> mImpl;
};


int main()
{
    DispatchTask task1(MakeImpl([](Internal){ std::cout << 1 << std::endl; }));
    
    // return type is void
    task1(Internal()); 
    
    
    auto impl = MakeImplWithFuture([](Internal){ return 2; });
    auto fut = impl->get_future();
    
    DispatchTask task2(std::move(impl));
    
    // run the task
    task2(Internal());
    
    
    // get the result from the future
    std::cout << fut.get() << std::endl;
    
    // TODO: implement ImplWithCallback<F>
}

