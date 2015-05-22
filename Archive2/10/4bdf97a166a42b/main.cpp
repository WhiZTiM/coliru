#ifndef TIMEWINDOWCOUNTER
#define TIMEWINDOWCOUNTER

#include <iostream>
#include <boost/chrono.hpp>
#include <boost/atomic.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cmath>
#include <unistd.h>
//#include "../../Common/TimeAnalyser.hpp"

struct TimeAnalyser {
    double getClockTime() const { return 0; }
    boost::chrono::duration<double> getDiffTime_rt(double, double) const { return boost::chrono::milliseconds(1); }
};

using namespace std;

class TimeWindowCounter {

    TimeAnalyser timeAnalyser;
    boost::asio::io_service io;

  public:
    TimeWindowCounter();
    ~TimeWindowCounter();

    TimeWindowCounter(double currTime);

    boost::atomic<bool> first_order_sent;
    boost::chrono::duration<double> interval;

    double startTime;
    double stopTime;
    double endTime;
    double currTime;

    void init();

    int numberofOrders;
    int orderCount;

    int numberofOrder[99];
    int ind;

    boost::chrono::duration<double> WindowSize;
    int N; // WindowSize
    void addOrder();
    void clockTick(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count,
                   double* currTime); // 10ms or 100 times a second
    int getNumOfOrders();
    void timer_thread();
    void run();
};

#endif
//#include "TimeWindowCounter.hpp"
#include <iostream>
//#include "../../Common/TimeAnalyser.hpp"

TimeWindowCounter::TimeWindowCounter() { init(); }

void TimeWindowCounter::init() { boost::atomic<bool> first_order_sent(false); }

TimeWindowCounter::TimeWindowCounter(double currTime)
{
    first_order_sent = true;
    startTime = currTime;
    endTime = currTime;
    orderCount = 0;
    ind = 0;
    N = 1000;
    for (int j = 0; j <= 99; j++)
        numberofOrder[j] = 0;
}

TimeWindowCounter::~TimeWindowCounter() {}

void TimeWindowCounter::addOrder()
{
    orderCount++;
    numberofOrder[ind] = orderCount;
}

void TimeWindowCounter::clockTick(const boost::system::error_code& /*e*/, boost::asio::deadline_timer* t, int* count,
                                  double* currTime)
{

    stopTime = *currTime;
    WindowSize = timeAnalyser.getDiffTime_rt(startTime, stopTime);
    if (WindowSize.count() * 1000 > N)
        startTime = startTime + (WindowSize.count() * 1000 - N);
    ind = (ind + 1) % 10;

    std::cout << *count << std::endl;
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::milliseconds(1));
    t->async_wait(boost::bind(&TimeWindowCounter::clockTick, this, boost::asio::placeholders::error, t, count, currTime));

} // 10ms or 100 times a second

int TimeWindowCounter::getNumOfOrders()
{
    int sum = 0;
    for (int i = 0; i <= 99; i++)
        sum = sum + numberofOrder[i];
    return sum;
}

void TimeWindowCounter::run() { io.run(); }

int main()
{

    boost::asio::io_service io;

    int count = 0;
    TimeAnalyser timeAnalyser;
    double currTime = timeAnalyser.getClockTime();
    TimeWindowCounter* timewindowCounter = new TimeWindowCounter();
    boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(10));

    t.async_wait(boost::bind(&TimeWindowCounter::clockTick, timewindowCounter, boost::asio::placeholders::error, &t, &count, &currTime));

    timewindowCounter->run();

    for (int j = 0; j <= 100000; j++)
        timewindowCounter->addOrder();
    std::cout << "Final count is " << count << std::endl;
}
