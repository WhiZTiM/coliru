#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std::literals::chrono_literals;

struct timer_killer {
  // returns false if killed:
  template<class R, class P>
  bool wait_for( std::chrono::duration<R,P> const& time ) {
    std::unique_lock<std::mutex> lock(m);
    return !cv.wait_for(lock, time, [&]{return terminate;});
  }
  void kill() {
    std::unique_lock<std::mutex> lock(m);
    terminate=true;
    cv.notify_all();
  }
private:
  std::condition_variable cv;
  std::mutex m;
  bool terminate = false;
};

timer_killer bob;

int main() {
    std::vector< std::future<void> > tasks;
	tasks.push_back( std::async(std::launch::async,[]{
		while(bob.wait_for(500ms))
			std::cout << "thread 1 says hi\n";
        std::cout << "thread 1 dead\n";
	}));
	bob.wait_for(250ms);
	tasks.push_back( std::async(std::launch::async,[]{
		while(bob.wait_for(500ms))
			std::cout << "thread 2 says hi\n";
        std::cout << "thread 2 dead\n";
	}));
	bob.wait_for(1000ms);
    std::cout << "killing threads\n";
	bob.kill();
	for (auto&& f:tasks)
		f.wait();
	std::cout << "done\n";
	// your code goes here
	return 0;
}