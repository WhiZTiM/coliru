#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <folly/ScopeGuard.h>
#include <chrono>


#define TRACE std::cout << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__ << std::endl;
boost::asio::io_service ios;


struct Dispatcher
{
    using Storage = std::aligned_storage<3 * sizeof(long), alignof(long)>::type;

    Dispatcher() :
        mStrand(ios)
    {
        std::cout << "sizeof(DispatchTask)=" << sizeof(DispatchTask) << std::endl;
    }


    // post without return value
    template<typename F>
    void post(F&& f)
    {
        using tag = typename std::conditional<sizeof(f) <= sizeof(Storage), small_t, big_t>::type;
        post_impl(std::forward<F>(f), tag());
    }

//private:
    using Timer = boost::asio::deadline_timer;

    enum small_t { small };
    enum big_t { big };
    enum rvalue_ref_t { rvalue_ref };
    enum lvalue_ref_t { lvalue_ref };

    // post without return value
    template<typename F, typename Tag>
    auto post_impl(F&& f, Tag tag) -> typename std::enable_if<std::is_rvalue_reference<decltype(f)>::value>::type
    {
        postImpl(DispatchTask(std::forward<F>(f), tag, rvalue_ref));
    }

    // post without return value
    template<typename F, typename Tag>
    auto post_impl(F&& f, Tag tag) -> typename std::enable_if<std::is_lvalue_reference<decltype(f)>::value>::type
    {
        postImpl(DispatchTask(std::forward<F>(f), tag, lvalue_ref));
    }


    struct DispatchTask
    {
        using this_type = DispatchTask;

        template<typename F>
        DispatchTask(F&& f, small_t, rvalue_ref_t) :
            mFPtr([](this_type* task)
            {
                F& f = *static_cast<F*>(static_cast<void*>(&task->mStorage));
                SCOPE_EXIT {
                    f.~F();
                    task->mStorage = Storage();
                    task->mFPtr = nullptr;
                };
                f();
            })
        {
            static_assert(sizeof(f) <= sizeof(mStorage), "");
            new (&mStorage) F(std::move(f));
        }

        template<typename F>
        DispatchTask(F&& f, big_t, rvalue_ref_t) :
            mFPtr([](this_type* task) {
                F* fptr;
                memcpy(&fptr, &task->mStorage, sizeof(fptr));
                SCOPE_EXIT {
                    delete fptr;
                    task->mFPtr = nullptr;
                };
                (*fptr)();
            })
        {
            static_assert(sizeof(f) > sizeof(mStorage), "");
            F* fptr = new F(std::move(f));
            memcpy(&mStorage, &fptr, sizeof(fptr));
        }

        template<typename F>
        DispatchTask(F&& f, small_t, lvalue_ref_t) = delete;

        template<typename F>
        DispatchTask(F&& f, big_t, lvalue_ref_t) = delete;

        DispatchTask(DispatchTask&& rhs) noexcept :
            mFPtr(rhs.mFPtr),
            mStorage(rhs.mStorage)
        {
            rhs.mStorage = Storage();
            rhs.mFPtr = nullptr;
        }

        DispatchTask& operator=(DispatchTask&&) noexcept = delete;

        ~DispatchTask()
        {
            assert(!mFPtr);
        }

        void operator()()
        {
            mFPtr(this);
        }

        using FPtr = void (*)(DispatchTask*);
        FPtr mFPtr;
        Storage mStorage;
    };

    void postImpl(DispatchTask&& task)
    {
        auto was_empty = false;
        {
            std::lock_guard<std::mutex> lock(mMutex);
            was_empty = mTasks.empty();
            mTasks.push_back(std::move(task));
        }
        if (was_empty)
        {
            mStrand.post([this]{ run(); });
        }
    }

    void run()
    {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            std::swap(mTasks, mTasks2);
        }

        for (auto& task : mTasks2)
        {
            task();
        }
        mTasks2.clear();
    }

    std::mutex mMutex;
    std::vector<DispatchTask> mTasks;
    std::vector<DispatchTask> mTasks2;
    boost::asio::io_service::strand mStrand;
};


int main()
{


    Dispatcher dispatcher1;
    struct Big
    {
        Big()
        {
            l[0] = 0;
            l[1] = 1;
            l[2] = 2;
            l[3] = 3;
        }
        ~Big() {}
        long l[4];
    };
    Big big;
    dispatcher1.post([big]{ std::cout << "Big test: " << big.l[0]  << big.l[1]  << big.l[2]  << big.l[3] << '\n';; });



    struct Small
    {
        int small = 1234;
    };

    {
        TRACE
        Small small;
        TRACE
        dispatcher1.post([small] { std::cout << "Small test: " << small.small << '\n'; });
        TRACE
    }


//    auto teest = []{};
//    Dispatcher::DispatchTask task(teest, Dispatcher::small);


ios.run();

//dispatcher1.post([small] { std::cout << "Small test: " << small.small << '\n'; });
//ios.stop();
//ios.reset();

}
