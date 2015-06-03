#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>


int relative_ms() {
    using boost::posix_time::second_clock;
    static auto t0 = second_clock::local_time();

    return (second_clock::local_time() - t0).total_milliseconds();
}

boost::mutex mutex;

static void scheduler()
{
    boost::unique_lock<boost::mutex> lock(mutex);
    std::cout << "Enter " << __FUNCTION__ << " at " << relative_ms() << "ms\n";

    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    std::cout << "Leave " <<  __FUNCTION__ << " at " << relative_ms() << "ms\n";
}

void usb()
{
    boost::unique_lock<boost::mutex> lock(mutex);
    std::cout << "Enter " <<  __FUNCTION__ << " at " << relative_ms() << "ms\n";

    boost::this_thread::sleep_for(boost::chrono::seconds(5));

    std::cout << "Leave " <<  __FUNCTION__ << " at " << relative_ms() << "ms\n";
}

int main()
{
    std::cout << "Enter " <<  __FUNCTION__ << " at " << relative_ms() << "ms\n";
    boost::thread thread1(usb);
    boost::thread thread2(scheduler);
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    std::cout << "Leave " <<  __FUNCTION__ << " at " << relative_ms() << "ms\n";
}
