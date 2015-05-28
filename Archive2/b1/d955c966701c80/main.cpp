#include <type_traits>
#include <future>
#include <memory>
#include <iostream>
#include <sstream>
#include <utility>


// Logging utility
struct LogItem
{
    ~LogItem()
    {
        static std::mutex m;
        std::lock_guard<std::mutex> l(m);
        std::cout << ss.str() << std::endl;
    }
    std::stringstream ss;
};


#define LOG() if (false) ; else LogItem().ss


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


// Creating a ImplWithCallback<F> object requires us to know the type of
// the passed function object. If a lambda is used then we need this
// helper function to deduce its type.
template<typename F>
std::shared_ptr<ImplWithFuture<F>> MakeImplWithFuture(const F& f)
{
    return std::make_shared<ImplWithFuture<F>>(f);
}


//! ImplWithCallback bundles the task with Callback and promise.
template<typename F, typename Callback>
struct ImplWithCallback : ImplBase
{
    // F and Callback are typically a lambdas, but can be any callable object.

    ImplWithCallback(F f, Callback cb) :
        ImplBase([](Internal in, ImplBase& base){ static_cast<ImplWithCallback&>(base).run(in); }),
        f_(std::move(f)),
        callback_(cb)
    {
    }

    using R = decltype(std::declval<F>()(std::declval<Internal>()));

    void run(Internal in)
    {
        std::promise<R> prom;
        SetPromise(prom, f_, in);
        callback_(in, prom.get_future());
    }

    F f_;
    Callback callback_;
};


// Creating a ImplWithCallback<F> object requires us to know the type of
// the passed function object. If a lambda is used then we need this
// helper function to deduce its type.
template<typename F, typename Callback>
std::shared_ptr<ImplWithCallback<F, Callback>> MakeImplWithCallback(const F& f, const Callback& cb)
{
    return std::make_shared<ImplWithCallback<F, Callback>>(f, cb);
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


template<typename F>
void test_simple(F f)
{
    DispatchTask task1(MakeImpl(f));

    std::thread([=]{ task1(Internal()); }).detach(); // disconnect the thread from our scope

    // return immediately
}


// Returns a future carrying the return value of F.
template<typename F>
auto test_future(F f) -> std::future<decltype(f(Internal()))>
{
    // the impl needs to be created beforehand so we can get the future.
    auto impl = MakeImplWithFuture(f);
    auto fut = impl->get_future();

    // create the task
    DispatchTask task2(std::move(impl));

    // this may run in a background thread
    std::thread([=]{ task2(Internal()); }).detach();

    // return the future result immediately
    return fut;
}

template<typename F, typename Callback>
void test_callback(F f, Callback callback)
{
    // create the task
    DispatchTask task3(MakeImplWithCallback(f, callback));

    // run the task in background thread
    std::thread([=]{ task3(Internal()); }).detach();

    // return immediately
}


int main()
{
    // test simple task
    auto f1 = [](Internal) { LOG() << 1; };
    test_simple(f1);

    // test with future
    auto f2 = [](Internal){ return 2; };
    std::future<int> fut = test_future(f2);
    LOG() << fut.get();

    // test with callback
    auto f3 = [](Internal){ return 3; };
    auto callback = [](Internal, std::future<int> fut) { LOG() << fut.get(); };
    test_callback(f3, callback);
    
    // wait a little for all tasks to complete
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

