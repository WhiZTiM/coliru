//
// Thunderbolt is a high-performance and highly-scalable thread pool implementation.
// Dependencies:
//               C++11, Boost.Lockfree.
// Documentation:
//                See: java.util.concurrent.ThreadPoolExecutor
// file name: threadpoolexecutor.hpp
//



#ifndef THREAD_POOL_EXECUTOR_HPP 
#define THREAD_POOL_EXECUTOR_HPP 

#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>
#include <boost/lockfree/queue.hpp>



#include <iostream>
int threadNo = 0;
std::mutex stdCoutMutex_;



namespace concurrent {
class ThreadPoolExecutor {
protected:
    typedef void (*Command) (void *);
	struct Task {
		Command command;
		void *arg;
	};

public:
	// Creates a new ThreadPoolExecutor with the given initial parameters.
	// Construct task queue, allocate n nodes for the freelist. 
	explicit ThreadPoolExecutor(std::size_t n) 
		: taskQueue_(n)
		, shutdownNow_(false)
		, corePoolSize_((std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency())
		, maximumPoolSize_((std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency())
		, poolSize_(0)
		, keepAliveTime_(5 * 60 * 1000)
		, taskQueueSize_(0)
		, completedTaskCount_(0)
		, taskCount_(0)
		, largestPoolSize_(0)
	{ 
	}
	ThreadPoolExecutor( const ThreadPoolExecutor& ) = delete; 
	ThreadPoolExecutor( ThreadPoolExecutor&& ) = delete; 
	ThreadPoolExecutor& operator=( const ThreadPoolExecutor& ) = delete; 
	ThreadPoolExecutor& operator=( ThreadPoolExecutor&& ) = delete; 

	virtual ~ThreadPoolExecutor() { 
	}

	virtual void exceptionHandling(const char* what) { 
	}

	// command: the task to execute. Don't throw exceptions in this function.
	//     arg: argument that will be passed to command.
	void execute(void (*command) (void *), void *arg) {
		if (poolSize_ < maximumPoolSize_ && taskQueueSize_ + 1 > poolSize_) {
			CreateThread();
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "if (poolSize_ < maximumPoolSize_ && taskQueueSize_ + 1 > poolSize_) {" << '\n';}
		}

		Task newTask;
		newTask.command = command;
		newTask.arg = arg;

		while (!taskQueue_.push(newTask))
			;

		++ taskQueueSize_;
		++ taskCount_;
		conditionVariable_.notify_one();
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "conditionVariable_.notify_one();" << '\n';}

		if (largestPoolSize_ < poolSize_) {
			std::size_t temp = poolSize_;
			largestPoolSize_ = temp;
		}
	}

	std::size_t getCompletedTaskCount() {
		return completedTaskCount_;
	}

	std::size_t getCorePoolSize() {
		return corePoolSize_; 
	}

	// Time Unit: milliseconds 
	std::size_t getKeepAliveTime() {
		return keepAliveTime_;
	}

	std::size_t getLargestPoolSize() {
		return largestPoolSize_;
	}

	std::size_t getMaximumPoolSize() {
		return maximumPoolSize_; 
	}

	std::size_t getPoolSize() {
		return poolSize_;
	}

	std::size_t getTaskQueueSize() {
		return taskQueueSize_;
	}

	std::size_t getTaskCount() {
		return taskCount_;
	}

	void PrestartAllCoreThreads() {
		while (poolSize_ < corePoolSize_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "PrestartAllCoreThreads()-->" << "poolSize_ = " << poolSize_ << ";corePoolSize_ = " << corePoolSize_ << '\n';}
			CreateThread();
		}
	}

	void setCorePoolSize(std::size_t corePoolSize) { 
		corePoolSize_ = corePoolSize; 
	}

	// Time Unit: milliseconds 
	void setKeepAliveTime(std::size_t keepAliveTime) {
		keepAliveTime_ = keepAliveTime;
	}

	void setMaximumPoolSize(std::size_t maximumPoolSize) {
		maximumPoolSize_ = maximumPoolSize; 
	}

	void ShutdownNow() {
		shutdownNow_ = true;
		conditionVariable_.notify_all();
	}

protected:
	inline void CreateThread() {
		try {
//			std::thread t(&ThreadPoolExecutor::StartRoutine, this);
			++threadNo;
			std::thread t(&ThreadPoolExecutor::StartRoutine, this, threadNo);

			t.detach();

			++ poolSize_;
		} catch(const std::exception& e) {
			exceptionHandling(e.what());
		} catch(...) {
			exceptionHandling("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
		}
	}


//	void StartRoutine() {
	void StartRoutine(std::size_t i) {
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "void StartRoutine(std::size_t i) {" << '\n';}

		Task t;
		bool terminateTheThread = false;
		bool timerEnabled = false;

		while (!shutdownNow_ && !terminateTheThread) {
			try {
				do {
					std::unique_lock<std::mutex> lk(mutex_);
					if (timerEnabled) {
						conditionVariable_.wait_for(lk, std::chrono::milliseconds(keepAliveTime_));
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "conditionVariable_.wait_for.woken up or timeout" << '\n';}
					} else {
						conditionVariable_.wait(lk);
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "conditionVariable_.wait.woken up" << '\n';}
					}
				} while(0);

				while (!shutdownNow_) {
					if (taskQueue_.pop(t)) {
						// order
						-- taskQueueSize_;
						timerEnabled = false;
						t.command(t.arg);
						++ completedTaskCount_;
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (taskQueue_.pop(t)) {" << '\n';}
					} else {
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);" << '\n';}
						std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);
						if (poolSize_ > corePoolSize_) {
							if (!timerEnabled) {
								timerEnabled = true;
								{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (!timerEnabled) {" << '\n';}
							} else {
								-- poolSize_;
								terminateTheThread = true;
								{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "terminateTheThread = true;" << '\n';}
							}
						}

						break;
					}
				}
			} catch(const std::exception& e) {
				exceptionHandling(e.what());
			} catch(...) {
				exceptionHandling("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
			}
		}
	}

	boost::lockfree::queue<Task> taskQueue_;
	std::mutex terminateTheThreadMutex_;
	std::mutex mutex_;
	std::condition_variable conditionVariable_;
	std::atomic<bool> shutdownNow_;
	std::atomic<std::size_t> corePoolSize_;
	std::atomic<std::size_t> maximumPoolSize_;
	std::atomic<std::size_t> poolSize_;
	std::atomic<std::size_t> keepAliveTime_;
	std::atomic<std::size_t> taskQueueSize_;
	std::atomic<std::size_t> completedTaskCount_;
	std::atomic<std::size_t> taskCount_;
	std::atomic<std::size_t> largestPoolSize_;
};
}

#endif  // THREAD_POOL_EXECUTOR_HPP 


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Example
//
// Dependencies:
//               Linux 
//


//#include "threadpoolexecutor.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

class MyThreadPoolExecutor : public concurrent::ThreadPoolExecutor {
public:
	explicit MyThreadPoolExecutor(std::size_t n)
		: concurrent::ThreadPoolExecutor(n) 
	{ 
	}

	virtual ~MyThreadPoolExecutor() { 
	}

	// Don't throw exceptions in this function.
	virtual void exceptionHandling(const char* what) {
		try {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "exception = " << what << '\n';}
		} catch(...) {
		}
	}
};

std::atomic<bool> terminateTheProcess(false);
std::atomic<long> cnt(0);

void write_to_a_file_descriptor (void *arg) {
	cnt += *((long*)arg);
}

void read_from_a_file_descriptor (void *arg) {
}

void throw_std_error (void *arg) {
	throw std::runtime_error("std::runtime_error");
}

class Size { 
};

void throw_size (void *arg) {
	throw Size();
}

static void signal_handler(int sig, siginfo_t *si, void *unused) {
	terminateTheProcess = true;
}

int main() {
	// signal handling.
	// top(1), pid
	// kill pid
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("sigaction");

	do {
		MyThreadPoolExecutor tpe(128);
/*
		MyThreadPoolExecutor tpe_error(tpe);
		MyThreadPoolExecutor tpe_error2(std::move(tpe));

		MyThreadPoolExecutor tpe_error3(1);
		tpe_error3 = tpe;
		tpe_error3 = std::move(tpe);
*/

		std::cout << "std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << '\n';
		std::cout << "default settings:" << '\n';
		std::cout << "    corePoolSize = " << tpe.getCorePoolSize() << ", maximumPoolSize = " << tpe.getMaximumPoolSize() << ", keepAliveTime = " << tpe.getKeepAliveTime() << " ms." << '\n';
		std::size_t hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
		tpe.setCorePoolSize(hardware_concurrency*4);
		tpe.setMaximumPoolSize(hardware_concurrency*8);
		tpe.setKeepAliveTime(2 * 1000);
		std::cout << "new settings:" << '\n';
		std::cout << "    corePoolSize = " << tpe.getCorePoolSize() << ", maximumPoolSize = " << tpe.getMaximumPoolSize() << ", keepAliveTime = " << tpe.getKeepAliveTime() << " ms." << '\n';
		if (tpe.getCorePoolSize() == hardware_concurrency*4) std::cout << "setCorePoolSize() && getCorePoolSize() ok." << '\n';
		if (tpe.getMaximumPoolSize() == hardware_concurrency*8) std::cout << "setMaximumPoolSize() && getMaximumPoolSize() ok." << '\n';
		if (tpe.getKeepAliveTime() == 2 * 1000) std::cout << "setKeepAliveTime() && getKeepAliveTime() ok." << '\n';
		std::cout << "-----------------------------------------------------------------------------------" << '\n';


//		const long SIZE = 1000000;
		const long SIZE = hardware_concurrency*100;//1000;
		long in = 1;
		auto start = std::chrono::high_resolution_clock::now();
		tpe.PrestartAllCoreThreads();
		for (long i = 0;i < SIZE;++ i) {
			tpe.execute(write_to_a_file_descriptor, &in);
		}

		tpe.execute(throw_std_error, &in);
		tpe.execute(throw_size, &in);

		// ......

		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 1000);
			if (terminateTheProcess) {
				tpe.ShutdownNow();

				// Clean up.
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "Clean up." << '\n';}

				break;
			}

			// ......

			while (tpe.getTaskQueueSize() > 0)
				;

			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> difference = end - start;

			//kill(getpid(), SIGINT);
			kill(getpid(), SIGTERM);
			//kill(getpid(), SIGQUIT);
			std::this_thread::sleep_for(std::chrono::seconds(1));

			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "max threadNo = " << threadNo << '\n';}
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "time = " << difference.count() << " s\n";}
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "cnt = " << cnt << '\n';}
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "CompletedTaskCount = " << tpe.getCompletedTaskCount() << '\n';}
		}
	} while(0);

	return 0;
}

