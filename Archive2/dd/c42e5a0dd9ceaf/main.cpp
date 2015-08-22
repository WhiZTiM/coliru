#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>


template<typename T>
struct SharedState
{

    bool ready_ = false;
    std::aligned_storage<sizeof(T), alignof(T)> result_storage_;
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

    std::shared_ptr<SharedState<T>> mSharedState;
};


template<typename T>
struct Promise
{

    Promise() : mSharedState(std::make_shared<SharedState<T>>()) {}

    void set_value(const T& t)
    {
        {
            std::lock_guard<std::mutex> lock(mSharedState->mutex_);
            mSharedState->ready_ = true;
            mSharedState->result_ = t;
        }
        mSharedState->cond_.notify_one();
    }

    void set_value(T&& t)
    {
        {
            std::lock_guard<std::mutex> lock(mSharedState->mutex_);
            mSharedState->ready_ = true;
            new (&mSharedState->result_storage_) T(std::move(t));
        }
        mSharedState->cond_.notify_one();
    }

    Future<T> get_future()
    {
        return Future<T>(mSharedState);
    }

    std::shared_ptr<SharedState<T>> mSharedState;
};


int main()
{
    Promise<int> p;
    auto fut = p.get_future();
    std::thread t1([&]
    {
        p.set_value(42);
    });

    std::cout << fut.get() << std::endl;

    t1.join();
}
