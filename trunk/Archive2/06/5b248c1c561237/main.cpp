#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <functional>
#include <future>

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



template<typename ChronoType> class StopWatchAtomic {
   typedef std::chrono::steady_clock clock;
   uint64_t wait_time_till_flagging_;

   clock::time_point start_;
   std::atomic<bool> now_;
   std::atomic<bool> exit_flag_;
   std::thread timer_thread_;
   std::function<void()> sleepTill_;

 public:
//   typedef std::chrono::steady_clock clock;
//   typedef std::chrono::microseconds microseconds;
//   typedef std::chrono::milliseconds milliseconds;
//   typedef std::chrono::seconds seconds;


   StopWatchAtomic(uint64_t wait_time_till_flagging, std::function<void()> sleepTill) : wait_time_till_flagging_(wait_time_till_flagging), start_(clock::now()), now_(false), exit_flag_(false), timer_thread_(&StopWatchAtomic<ChronoType>::TimeRun, this), sleepTill_(sleepTill) {
      static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
      // FYI:  This would fail  static_assert(std::chrono::high_resolution_clock::is_steady(), "High Resolution Clock is NOT steady on CentOS?!");
   }
   StopWatchAtomic(const StopWatchAtomic& other) = delete;
   StopWatchAtomic& operator=(const StopWatchAtomic& rhs) = delete;


   ~StopWatchAtomic() {
      exit_flag_.store(true, std::memory_order_release);
      timer_thread_.join();
   }

   bool ElapsedChronoTime() {
      bool result = now_.load(std::memory_order_relaxed);
      if (result) {
         now_.store(false, std::memory_order_release );
      }
      return result;
   }

   std::chrono::steady_clock::time_point Restart() {
      start_ = clock::now();
      now_.store(false);
      return start_;
   }

 private:
   void TimeRun () {
      while (!exit_flag_.load(std::memory_order_relaxed)) {
         uint64_t elapsed = std::chrono::duration_cast<ChronoType>(clock::now() - start_).count();
         if (elapsed >= wait_time_till_flagging_) {
            now_.store(true, std::memory_order_release);
         }
         sleepTill_();
      }
   }

};


int main() {

   auto func = []() ->uint64_t{
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
      StopWatchAtomic<std::chrono::seconds> watch(uint64_t(5), []{std::this_thread::yield();});
      /*you could also use a longer sleep time in between runs: this would add granularity but decrease cpu load
      std::this_thread::sleep_for(std::chrono::microseconds(10)*/
      while (!watch.ElapsedChronoTime()) {
         ;;
      }
      auto stopUs = check.ElapsedUs();
      return stopUs;
   };
   auto futureElapsedUs2 = std::async(std::launch::async, func2);
   std::cout << "Elapsed us for atomic threaded 5s wait " << futureElapsedUs2.get()  << std::endl;


}