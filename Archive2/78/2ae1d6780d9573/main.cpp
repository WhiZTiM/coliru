#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

/// Wrapper for std::thread that automatically joins at end of scope.
class JoiningThread
{
   public:
      /// Constructor taking a Function with its arguments.
      template <typename Function, typename... Args>
      JoiningThread(Function&& f, Args&&... args)
      :
       	thread(std::forward<Function>(f), std::forward<Args>(args)...)
   	  {
   	  }
      JoiningThread(JoiningThread&&) = default;
      ~JoiningThread()
      {
      	thread.join();
      }
      JoiningThread(const JoiningThread&) = delete;
      JoiningThread& operator=(const JoiningThread&) = delete;
   private:
      std::thread thread;
};

class CallBackTimer
{
	public:
    	CallBackTimer(int interval, std::function<void(void)> func)
    	:
    		execute(true),
    		thread([=]()
	        {
	            while ( execute )
	            {
	                func();                   
	                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
	            }
	        })
    	{
    	}
	    void stop()
	    {
	        execute = false;
	    }
	private:
	    std::atomic<bool> execute;
	    JoiningThread thread;
};

struct Processor
{
	void foo()
	{
        std::cerr << "foo!\n";
	}
};

int main()
{
	Processor p;
	CallBackTimer cbt(250, std::bind(&Processor::foo, &p));
	std::this_thread::sleep_for(std::chrono::seconds(1));
	cbt.stop();
	return 0;
}