#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <iostream>

#define TRACE(msg) do { std::cout << msg << " " << __FUNCTION__ << " at " << relative_ms() << "ms\n"; } while(false)

int relative_ms() {
    using boost::posix_time::second_clock;
    static auto t0 = second_clock::local_time();

    return (second_clock::local_time() - t0).total_milliseconds();
}

boost::mutex mutex;

static void scheduler()
{
    boost::unique_lock<boost::mutex> lock(mutex);
    TRACE("Enter");

    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    TRACE("Leave");
}

void usb()
{
    boost::unique_lock<boost::mutex> lock(mutex);
    TRACE("Enter");

    boost::this_thread::sleep_for(boost::chrono::seconds(5));

    TRACE("Leave");
}

int main()
{
    TRACE("Enter");
    boost::thread thread1(usb);
    boost::thread thread2(scheduler);
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    TRACE("Leave");
}
