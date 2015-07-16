#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <functional>
#include <future>
#include <mutex>
#include <cassert>
/*
 * File:   StopWatch.cpp
 * Author: KjellKod
 * From: https://github.com/KjellKod/StopWatch
 *
 * Created on 2014-02-07
 */

#include <chrono>


class StopWatch {
 public:
   typedef std::chrono::steady_clock clock;
   typedef std::chrono::microseconds microseconds;
   typedef std::chrono::milliseconds milliseconds;
   typedef std::chrono::seconds seconds;

   StopWatch() : mStart(clock::now()) {
      static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
      // FYI:  This would fail  static_assert(std::chrono::high_resolution_clock::is_steady(), "High Resolution Clock is NOT steady on CentOS?!");
   }
   StopWatch(const StopWatch& other): mStart(other.mStart) {
   }
   StopWatch& operator=(const StopWatch& rhs) {
      mStart = rhs.mStart;
      return *this;
   }

   uint64_t ElapsedUs() const {
      return std::chrono::duration_cast<microseconds>(clock::now() - mStart).count();
   }
   uint64_t ElapsedMs() const {
      return std::chrono::duration_cast<milliseconds>(clock::now() - mStart).count();
   }

   uint64_t ElapsedSec() const {
      return std::chrono::duration_cast<seconds>(clock::now() - mStart).count();
   }

   std::chrono::steady_clock::time_point Restart() {
      mStart = clock::now();
      return mStart;
   }

 private:
   clock::time_point mStart;
};



template<typename ChronoType> class HasElapsed {
   typedef std::chrono::steady_clock clock;
   
   int64_t wait_time_till_flagging_;
   clock::time_point start_;
   std::atomic<bool> now_;
   std::atomic<bool> exit_flag_;
   std::unique_ptr<std::thread> timer_thread_;
   std::mutex m;

 public:
//   typedef std::chrono::steady_clock clock;
//   typedef std::chrono::microseconds microseconds;
//   typedef std::chrono::milliseconds milliseconds;
//   typedef std::chrono::seconds seconds;


   HasElapsed(int64_t wait_time_till_flagging) 
   : wait_time_till_flagging_(wait_time_till_flagging)
   , start_(clock::now()), now_(false), exit_flag_(false)
   , timer_thread_(new std::thread(&HasElapsed<ChronoType>::TimeRun, this)) 
   {
      static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
      assert(wait_time_till_flagging_ != 0);
   }
   
   
   HasElapsed(const HasElapsed& other) = delete;
   HasElapsed& operator=(const HasElapsed& rhs) = delete;


   ~HasElapsed() {
      exit_flag_.store(true, std::memory_order_release);
      timer_thread_->join();
   }

   bool Enough() {
      return now_.load(std::memory_order_relaxed);
   }

   std::chrono::steady_clock::time_point Restart(uint64_t) {
       std::lock_guard<std::mutex> guard(m);
       start_ = clock::now();
       now_.store(false);
       exit_flag_.store(true, std::memory_order_release);
       timer_thread_->join();
       exit_flag_.store(false, std::memory_order_release);
       timer_thread_.reset(new std::thread(&HasElapsed<ChronoType>::TimeRun, this));
       return start_;
   }

 private:
   void TimeRun () {
      while (!exit_flag_.load(std::memory_order_relaxed)) {
         uint64_t elapsed = std::chrono::duration_cast<ChronoType>(clock::now() - start_).count();
         if (elapsed >= wait_time_till_flagging_) {
            now_.store(true, std::memory_order_release);
         }
          /// We should probably sleep with granularity:
       /// if Chronotype is seconds: sleep 1 second at a time
       ///                  milliseconds: sleep 1ms at a time
       ///                  us: sleep 1us at a time
       /// otherwise we are stuck in case we need to exit while we are waiting for the time to elapse
      std::this_thread::sleep_for(ChronoType(wait_time_till_flagging_/wait_time_till_flagging_));
      }
   }

};


int main() {

   auto func = []() ->int64_t{
      StopWatch check;
      StopWatch watch;
      while (watch.ElapsedSec() < 5) {
         ;;
      }
      auto stopUs = check.ElapsedUs();
      return stopUs;
   };

   auto futureElapsedUs = std::async(std::launch::async, func);
   std::cout << "Elapsed us for 5s wait " << futureElapsedUs.get()  << std::endl;

   auto func2 = []() ->uint64_t{
      StopWatch check;
      using TimeChecker = HasElapsed<std::chrono::seconds>;
      TimeChecker  watch(int64_t(5));      
      while (!watch.Enough()) {
         ;;
      }
      auto stopUs = check.ElapsedUs();
      return stopUs;
   };
   auto futureElapsedUs2 = std::async(std::launch::async, func2);
   std::cout << "Elapsed us for atomic threaded 5s wait " << futureElapsedUs2.get()  << std::endl;


}
