//
// Thunderbolt is a high-performance and highly-scalable thread pool implementation.
// Dependencies:
//               C++11, Boost.Lockfree.
// Documentation:
//                See: java.util.concurrent.ThreadPoolExecutor
// file name: threadpool.hpp
//



#ifndef THREAD_POOL_HPP 
#define THREAD_POOL_HPP 

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



namespace ThreadPool {
class ThreadPool {
protected:
    typedef void (*Command) (void *);
	struct Task {
		Command command;
		void *arg;
	};

public:
	// Creates a new ThreadPoolExecutor with the given initial parameters.
	// Construct task Queue, allocate n nodes for the freelist. 
	explicit ThreadPool(std::size_t n) : 
		taskQueue_(n),
		shutdownNow_(false),
		corePoolSize_((std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency()),
		maximumPoolSize_((std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency()),
		poolSize_(0),
		keepAliveTime_(5 * 60 * 1000),
		taskQueueSize_(0),
		completedTaskCount_(0),
		taskCount_(0),
		largestPoolSize_(0)
	{ }
	ThreadPool( const ThreadPool& ) = delete; 
	ThreadPool( ThreadPool&& ) = delete; 
	ThreadPool& operator=( const ThreadPool& ) = delete; 
	ThreadPool& operator=( ThreadPool&& ) = delete; 

	virtual ~ThreadPool() { }

	virtual void ExceptionHandling(const char* what) { }

	// command: the task to execute. Don't throw exceptions in this function.
	//     arg: argument that will be passed to command.
	void Execute(void (*command) (void *), void *arg) {
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

	std::size_t GetCompletedTaskCount() {
		return completedTaskCount_;
	}

	std::size_t GetCorePoolSize() {
		return corePoolSize_; 
	}

	// Time Unit: milliseconds 
	std::size_t GetKeepAliveTime() {
		return keepAliveTime_;
	}

	std::size_t GetLargestPoolSize() {
		return largestPoolSize_;
	}

	std::size_t GetMaximumPoolSize() {
		return maximumPoolSize_; 
	}

	std::size_t GetPoolSize() {
		return poolSize_;
	}

	std::size_t GetTaskQueueSize() {
		return taskQueueSize_;
	}

	std::size_t GetTaskCount() {
		return taskCount_;
	}

	void PrestartAllCoreThreads() {
		while (poolSize_ < corePoolSize_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "PrestartAllCoreThreads()-->" << "poolSize_ = " << poolSize_ << ";corePoolSize_ = " << corePoolSize_ << '\n';}
			CreateThread();
		}
	}

	void SetCorePoolSize(std::size_t corePoolSize) { 
		corePoolSize_ = corePoolSize; 
	}

	// Time Unit: milliseconds 
	void SetKeepAliveTime(std::size_t keepAliveTime) {
		keepAliveTime_ = keepAliveTime;
	}

	void SetMaximumPoolSize(std::size_t maximumPoolSize) {
		maximumPoolSize_ = maximumPoolSize; 
	}

	void ShutdownNow() {
		shutdownNow_ = true;
		conditionVariable_.notify_all();
	}

protected:
	inline void CreateThread() {
		try {
//			std::thread t(&ThreadPool::StartRoutine, this);
			++threadNo;
			std::thread t(&ThreadPool::StartRoutine, this, threadNo);

			t.detach();

			++ poolSize_;
		} catch(const std::exception& e) {
			ExceptionHandling(e.what());
		} catch(...) {
			ExceptionHandling("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
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
				ExceptionHandling(e.what());
			} catch(...) {
				ExceptionHandling("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
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

#endif  // THREAD_POOL_HPP 


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Example
//
// Dependencies:
//               Linux 
//


//#include "threadpool.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

class MyThreadPool : public ThreadPool::ThreadPool {
public:
	explicit MyThreadPool(std::size_t n): ThreadPool::ThreadPool(n) { }

	virtual ~MyThreadPool() { }

	// Don't throw exceptions in this function.
	virtual void ExceptionHandling(const char* what) {
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
		MyThreadPool tp(12345);
/*
		ThreadPool::ThreadPool tp_error(tp);
		ThreadPool::ThreadPool tp_error2(std::move(tp));

		ThreadPool::ThreadPool tp_error3(1);
		tp_error3 = tp;
		tp_error3 = std::move(tp);
*/

		std::cout << "std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << '\n';
		std::cout << "default settings:" << '\n';
		std::cout << "    corePoolSize = " << tp.GetCorePoolSize() << ", maximumPoolSize = " << tp.GetMaximumPoolSize() << ", keepAliveTime = " << tp.GetKeepAliveTime() << " ms." << '\n';
		std::size_t hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
		tp.SetCorePoolSize(hardware_concurrency*4);
		tp.SetMaximumPoolSize(hardware_concurrency*8);
		tp.SetKeepAliveTime(2 * 1000);
		std::cout << "new settings:" << '\n';
		std::cout << "    corePoolSize = " << tp.GetCorePoolSize() << ", maximumPoolSize = " << tp.GetMaximumPoolSize() << ", keepAliveTime = " << tp.GetKeepAliveTime() << " ms." << '\n';
		if (tp.GetCorePoolSize() == hardware_concurrency*4) std::cout << "SetCorePoolSize() && GetCorePoolSize() ok." << '\n';
		if (tp.GetMaximumPoolSize() == hardware_concurrency*8) std::cout << "SetMaximumPoolSize() && GetMaximumPoolSize() ok." << '\n';
		if (tp.GetKeepAliveTime() == 2 * 1000) std::cout << "SetKeepAliveTime() && GetKeepAliveTime() ok." << '\n';
		std::cout << "-----------------------------------------------------------------------------------" << '\n';


//		const long SIZE = 1000000;
		const long SIZE = hardware_concurrency*100;//1000;
		long in = 1;
		auto start = std::chrono::high_resolution_clock::now();
		tp.PrestartAllCoreThreads();
		for (long i = 0;i < SIZE;++ i) {
			tp.Execute(write_to_a_file_descriptor, &in);
		}

		tp.Execute(throw_std_error, &in);
		tp.Execute(throw_size, &in);

		// ......

		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 1000);
			if (terminateTheProcess) {
				tp.ShutdownNow();

				// Clean up.
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "Clean up." << '\n';}

				break;
			}

			// ......

			while (tp.GetTaskQueueSize() > 0)
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
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "CompletedTaskCount = " << tp.GetCompletedTaskCount() << '\n';}
		}
	} while(0);

	return 0;
}


