#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>


template<typename T>
struct Future;


template<typename T>
auto MakeReadyFuture(T&& t) -> Future<typename std::decay<T>::type>;


// for making a future<void>
auto MakeReadyFuture() -> Future<void>;


template<typename T>
struct SharedState
{
    using ContinuationPtr = void (*) (Future<T>);

    bool ready_ = false;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type result_storage_{};
    ContinuationPtr continuation_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

template<>
struct SharedState<void>
{
    using ContinuationPtr = void (*) (Future<void>);

    bool ready_ = false;
    ContinuationPtr continuation_ = nullptr;
    std::mutex mutex_;
    std::condition_variable cond_;
};


template<typename T>
struct Future
{
    Future(const std::shared_ptr<SharedState<T>>& inSharedState) :
        mSharedState(inSharedState)
    {
    }

    T get()
    {
        std::unique_lock<std::mutex> lock(mSharedState->mutex_);
        while (!mSharedState->ready_)
        {
            mSharedState->cond_.wait(lock);
        }
        return std::move(*static_cast<T*>(static_cast<void*>(&mSharedState->result_storage_)));
    }

    template<typename F>
    auto then(F&& f) -> void
    {
        std::lock_guard<std::mutex> lock(mSharedState->mutex_);
        this->mSharedState->continuation_ = f;

    }

    std::shared_ptr<SharedState<T>> mSharedState;
};


template<>
struct Future<void>
{
    Future(const std::shared_ptr<SharedState<void>>& inSharedState) :
        mSharedState(inSharedState)
    {
    }

    void get()
    {
        std::unique_lock<std::mutex> lock(mSharedState->mutex_);
        while (!mSharedState->ready_)
        {
            mSharedState->cond_.wait(lock);
        }
    }

    template<typename F>
    auto then(F&& f) -> void
    {
        std::lock_guard<std::mutex> lock(mSharedState->mutex_);
        mSharedState->continuation_ = f;

    }

    std::shared_ptr<SharedState<void>> mSharedState;
};


template<typename T>
struct PromiseImpl
{
    PromiseImpl() : mSharedState(std::make_shared<SharedState<T>>()) {}

    void set_value(const T& t);

    void set_value(T&& t);

    std::shared_ptr<SharedState<T>> mSharedState;
};


template<>
struct PromiseImpl<void>
{
    PromiseImpl() : mSharedState(std::make_shared<SharedState<void>>()) {}

    void set_value();

    std::shared_ptr<SharedState<void>> mSharedState;
};


template<typename T>
struct Promise : PromiseImpl<T>
{
    Future<T> get_future()
    {
        return Future<T>(this->mSharedState);
    }

};


/**
 * Make future that is already ready.
 *
 * Usage example:
 *  IPv4Session& ipSession = getIPv4Session();
 *  MakeReadyFuture<IPv4Session>(ipSession) // returns Future<IPv4Session>
 *  MakeReadyFuture<IPv4Session>(std::ref(ipSession)) // returns Future<IPv4Session&>
 */
template<typename T>
auto MakeReadyFuture(T&& t) -> Future<typename std::decay<T>::type>
{
    using CleanT = typename std::decay<T>::type;
    Promise<CleanT> prom;
    Future<CleanT> fut = prom.get_future();
    prom.set_value(std::forward<T>(t));
    return fut;
}


//// for making a future<void>
inline auto MakeReadyFuture() -> Future<void>
{
    Promise<void> prom;
    Future<void> fut = prom.get_future();
    prom.set_value();
    return fut;
}


// for making a future<void> that rethrows an exception
template<typename T, typename Exception>
auto MakeExceptionalFuture(Exception&& e) -> Future<T>
{
    Promise<T> prom;
    try { throw e; } catch (...) { prom.set_exception(std::current_exception()); }
    return prom.get_future();
}


// for making a future<void> that rethrows an exception
template<typename T>
auto MakeExceptionalFuture(std::exception_ptr eptr) -> Future<T>
{
    Promise<T> prom;
    prom.set_exception(eptr);
    return prom.get_future();
}


template<typename T>
inline void PromiseImpl<T>::set_value(const T& t)
{
    {
        std::lock_guard<std::mutex> lock(mSharedState->mutex_);

        mSharedState->ready_ = true;

        if (mSharedState->continuation_)
        {
            mSharedState->continuation_(MakeReadyFuture(t));
        }
        else
        {
            new (&mSharedState->result_storage_) T(t);
        }
    }

    mSharedState->cond_.notify_one();
}


template<typename T>
inline void PromiseImpl<T>::set_value(T&& t)
{
    {
        std::lock_guard<std::mutex> lock(mSharedState->mutex_);

        mSharedState->ready_ = true;

        if (mSharedState->continuation_)
        {
            mSharedState->continuation_(MakeReadyFuture(std::move(t)));
        }
        else
        {
            new (&mSharedState->result_storage_) T(std::move(t));
        }
    }

    mSharedState->cond_.notify_one();
}


void PromiseImpl<void>::set_value()
{
    {
        std::lock_guard<std::mutex> lock(mSharedState->mutex_);

        mSharedState->ready_ = true;

        if (mSharedState->continuation_)
        {
            mSharedState->continuation_(MakeReadyFuture());
        }
    }

    mSharedState->cond_.notify_one();
}



int main()
{
    Promise<int> p;
    auto fut = p.get_future();
    fut.then([](Future<int> result) {
        std::cout << "CALLBACK: " << result.get() << std::endl;
    });


    Promise<void> pv;
    auto futv = pv.get_future();
    futv.then([](Future<void> result) {
        result.get();
        std::cout << "VOID CALLBACK" << std::endl;
    });

    std::thread t1([&] {
        p.set_value(42);
        pv.set_value();
    });

    t1.join();
}

