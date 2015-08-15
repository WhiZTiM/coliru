#include <boost/asio.hpp>
#include <chrono>
#include <future>
#include <iostream>
#include <memory>


boost::asio::io_service ios;


struct Internal {};


struct Scheduler
{
    Scheduler(boost::asio::io_service& ios) :
        mStrand(ios)
    {
    }

    template<typename F>
    void post_no_return(F&& f)
    {
        mStrand.post([f]{ f(Internal{}); });
    }

    template<typename F>
    auto post(F&& f) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        using R = decltype(f(std::declval<Internal>()));
        using Task = std::packaged_task<R(Internal)>;
        auto task = std::make_shared<Task>(std::forward<F>(f));
        auto fut = task->get_future();
        mStrand.post([task]{ (*task)(Internal{}); });
        return fut;
    }

private:
    boost::asio::io_service::strand mStrand;
};


template<typename Future>
struct FuturePoller
{
    FuturePoller(Scheduler& scheduler, Future&& fut) :
        mImpl(std::make_shared<Impl>(scheduler, std::forward<Future>(fut)))
    {
        ios.post(*this);
    }

    void operator()()
    {
        if (std::future_status::timeout == mImpl->mFuture.wait_for(std::chrono::seconds(0)))
        {
            boost::asio::deadline_timer timer(ios);
            boost::system::error_code ec;
            timer.expires_from_now(boost::posix_time::milliseconds(1), ec);
            timer.async_wait([this](boost::system::error_code ec) { ios.post(*this); });
        }
        else
        {
            std::cout << mImpl->mFuture.get() << std::endl;

        }
    }

    struct Impl
    {
        Impl(Scheduler& scheduler, Future&& fut) :
            mScheduler(scheduler),
            mFuture(std::forward<Future>(fut))
        {
        }
        Scheduler& mScheduler;
        Future mFuture;
    };

    std::shared_ptr<Impl> mImpl;
};


template<typename Future>
FuturePoller<Future> MakeFuturePoller(Scheduler& scheduler, Future&& future)
{
    return FuturePoller<Future>(scheduler, std::forward<Future>(future));
}


int main()
{
    Scheduler task_scheduler(ios);
    Scheduler poller(ios);

    MakeFuturePoller(poller, task_scheduler.post([](Internal) {
        int limit = 3;
        while (limit--) {
            std::cout << "Wait for it!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return 42;
    }));

    ios.run();
}
