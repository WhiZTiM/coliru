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
		, shutdown_(false)
		, shutdownNow_(false)
		, corePoolSize_((std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency())
		, threshold_(10)
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

	// If timeout = 0, blocks until all tasks have completed execution.
	// Time Unit: milliseconds 
	bool awaitTermination(std::size_t timeout = 0) {
		if (timeout == 0) {
			while (poolSize_ > 0) {
				conditionVariable_.notify_all();
			}
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "in " << __func__ << ".-->if (timeout == 0) {" << '\n';}
			return true;
		} else {
			try {
				std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
			} catch(const std::exception& e) {
				eh(e.what());
			} catch(...) {
				eh("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
			}

			if (poolSize_ == 0) {
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "awaitTermination-->} else {-->return true;" << '\n';}
				return true;
			} else {
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "awaitTermination-->} else {-->return false;" << '\n';}
				return false;
			}
		}
	}

	// command: the task to execute. Don't throw exceptions in this function.
	//     arg: argument that will be passed to command.
	void execute(void (*command) (void *), void *arg) {
		if (shutdown_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "void execute(void (*command) (void *), void *arg) {-->if (shutdown_) {" << '\n';}
			return;
		}

		if (poolSize_ < corePoolSize_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "void execute(void (*command) (void *), void *arg) {-->if (poolSize_ < corePoolSize_) {-->" << "poolSize = " << poolSize_ << '\n';}
			createThread();
		} else if (poolSize_ < maximumPoolSize_ && taskQueueSize_/(poolSize_.load() > 0 ? poolSize_.load() : 1) > threshold_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "void execute(void (*command) (void *), void *arg) {-->} else if (poolSize_ < maximumPoolSize_ && taskQueueSize_/poolSize_ > threshold_) {-->" << "poolSize = " << poolSize_ << ";taskQueueSize_/poolSize_ = " << taskQueueSize_/poolSize_ << '\n';}
			createThread();
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

	std::size_t getTaskCount() {
		return taskCount_;
	}

	std::size_t getTaskQueueSize() {
		return taskQueueSize_;
	}

	std::size_t getThreshold() { 
		return threshold_;
	}

	void prestartAllCoreThreads() {
		while (poolSize_ < corePoolSize_) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "prestartAllCoreThreads()-->" << "poolSize = " << poolSize_ << '\n';}
			createThread();
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

	// If getCorePoolSize() <= getPoolSize() < getMaximumPoolSize() && getTaskQueueSize()/getPoolSize() > threshold, 
	// create a new thread.
	void setThreshold(std::size_t threshold) { 
		threshold_ = threshold;
	}

	void shutdown() {
		shutdown_ = true;
		conditionVariable_.notify_all();
	}

	void shutdownNow() {
		shutdownNow_ = true;
		conditionVariable_.notify_all();
	}

protected:
	virtual void exceptionHandling(const char* what) { 
	}

	inline void eh(const char* what) { 
		try {
			exceptionHandling(what);
		} catch(...) {
			{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "void eh(const char* what) {-->catch(...)" << '\n';}
		}
	}

	inline void createThread() {
		try {
//			std::thread t(&ThreadPoolExecutor::startRoutine, this);
			++threadNo;
			std::thread t(&ThreadPoolExecutor::startRoutine, this, threadNo);

			t.detach();

			++ poolSize_;
		} catch(const std::exception& e) {
			eh(e.what());
		} catch(...) {
			eh("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
		}
	}

//	void startRoutine() {
	void startRoutine(std::size_t i) {
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "void startRoutine(std::size_t i) {" << '\n';}

		Task t;
		bool terminateTheThread = false;
		bool timerEnabled = false;
		std::cv_status cvs = std::cv_status::no_timeout;
		std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
		std::chrono::duration<double, std::milli> difference;
		std::size_t timeout;

		while (1) {
			try {
				do {
					std::unique_lock<std::mutex> lk(mutex_);
					if (timerEnabled) {
						cvs = conditionVariable_.wait_for(lk, std::chrono::milliseconds(timeout));
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "conditionVariable_.wait_for.woken up or timeout" << '\n';}
					} else {
						conditionVariable_.wait(lk);
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "conditionVariable_.wait.woken up" << '\n';}
					}
				} while(0);

				if (shutdownNow_) {
					{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (shutdownNow_) {.-->outer 1" << '\n';}
					break;
				}

				while (1) {
					if (taskQueue_.pop(t)) {
						// order
						-- taskQueueSize_;
						timerEnabled = false;
						t.command(t.arg);
						++ completedTaskCount_;
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (taskQueue_.pop(t)) {" << '\n';}
					} else {
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "the queue is empty. std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);" << '\n';}
						std::lock_guard<std::mutex> lock(terminateTheThreadMutex_);
						if (poolSize_ > corePoolSize_) {
							if (!timerEnabled) {
								timerEnabled = true;
								start = std::chrono::high_resolution_clock::now();
								timeout = keepAliveTime_;
								{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (!timerEnabled) {" << '\n';}
							} else {
								if (cvs == std::cv_status::timeout) {
									terminateTheThread = true;
									{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "terminateTheThread = true;" << '\n';}
								} else {
									end = std::chrono::high_resolution_clock::now();
									difference = end - start;
									timeout = keepAliveTime_ - difference.count();
								}
							}
						}

						break;
					}

					if (shutdownNow_) {
						{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (shutdownNow_) {.-->inner" << '\n';}
						break;
					}
				}
			} catch(const std::exception& e) {
				eh(e.what());
			} catch(...) {
				eh("An exception of unknown type has occurred. All exceptions should inherit from std::exception.");
			}

			if (shutdown_) {
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (shutdown_) {" << '\n';}
				break;
			}

			if (shutdownNow_) {
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (shutdownNow_) {.-->outer 2" << '\n';}
				break;
			}

			if (terminateTheThread) {
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "if (terminateTheThread) {" << '\n';}
				break;
			}
		}
		-- poolSize_;
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "thread no. = " << i << ".  " << "exit. poolSize = " << poolSize_ << '\n';}
	}

	boost::lockfree::queue<Task> taskQueue_;
	std::mutex terminateTheThreadMutex_;
	std::mutex mutex_;
	std::condition_variable conditionVariable_;
	std::atomic<bool> shutdown_;
	std::atomic<bool> shutdownNow_;
	std::atomic<std::size_t> corePoolSize_;
	std::atomic<std::size_t> threshold_;
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

class Size { 
};

class MyThreadPoolExecutor : public concurrent::ThreadPoolExecutor {
public:
	explicit MyThreadPoolExecutor(std::size_t n)
		: concurrent::ThreadPoolExecutor(n) 
	{ 
	}

	virtual ~MyThreadPoolExecutor() { 
	}

protected:
	// Don't throw exceptions in this function.
	virtual void exceptionHandling(const char* what) {
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "exception = " << what << '\n';}
		throw Size();
	}
};

std::atomic<bool> terminateTheProcess(false);
std::atomic<long> cnt(0);

// Don't throw exceptions in this function.
void write_to_a_file_descriptor (void *arg) {
	cnt += *((long*)arg);
}

// Don't throw exceptions in this function.
void read_from_a_file_descriptor (void *arg) {
}

void throw_std_error (void *arg) {
	throw std::runtime_error("std::runtime_error");
}

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
		MyThreadPoolExecutor tpe(12345);
/*
		MyThreadPoolExecutor tpe_error(tpe);
		MyThreadPoolExecutor tpe_error2(std::move(tpe));

		MyThreadPoolExecutor tpe_error3(1);
		tpe_error3 = tpe;
		tpe_error3 = std::move(tpe);
*/
/*
		std::size_t k;
		k = 1;tpe.setCorePoolSize(k);if (tpe.getCorePoolSize() == k) std::cout << "setCorePoolSize() && getCorePoolSize() ok." << '\n';
		k = 2;tpe.setKeepAliveTime(k);if (tpe.getKeepAliveTime() == k) std::cout << "setKeepAliveTime() && getKeepAliveTime() ok." << '\n';
		k = 3;tpe.setMaximumPoolSize(k);if (tpe.getMaximumPoolSize() == k) std::cout << "setMaximumPoolSize() && getMaximumPoolSize() ok." << '\n';
		k = 4;tpe.setThreshold(k);if (tpe.getThreshold() == k) std::cout << "setThreshold() && getThreshold() ok." << '\n';
		std::cout << "-----------------------------------------------------------------------------------" << '\n';
*/
		std::cout << "std::thread::hardware_concurrency() = " << std::thread::hardware_concurrency() << '\n';
		std::cout << "default settings:" << '\n';
		std::cout << "    corePoolSize = " << tpe.getCorePoolSize() << ", maximumPoolSize = " << tpe.getMaximumPoolSize() << ", keepAliveTime = " << tpe.getKeepAliveTime() << " ms." << '\n';
		std::size_t hardware_concurrency = (std::thread::hardware_concurrency() == 0) ? 1 : std::thread::hardware_concurrency();
		tpe.setCorePoolSize(hardware_concurrency*4);
		tpe.setMaximumPoolSize(hardware_concurrency*8);
		tpe.setKeepAliveTime(100);tpe.setThreshold(2);
		std::cout << "new settings:" << '\n';
		std::cout << "    corePoolSize = " << tpe.getCorePoolSize() << ", maximumPoolSize = " << tpe.getMaximumPoolSize() << ", keepAliveTime = " << tpe.getKeepAliveTime() << " ms." << '\n';
		std::cout << "-----------------------------------------------------------------------------------" << '\n';


//		const long SIZE = 3000000;
		const long SIZE = hardware_concurrency*100;
		long in = 1;
		auto start = std::chrono::high_resolution_clock::now();
		tpe.prestartAllCoreThreads();
		for (long i = 0;i < SIZE;++ i) {
			tpe.execute(write_to_a_file_descriptor, &in);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1234));
		for (long i = 0;i < 4;++ i) {
			tpe.execute(write_to_a_file_descriptor, &in);
		}

	//	tpe.execute(throw_std_error, &in);
	//	tpe.execute(throw_size, &in);

		// ......

		for (;;) {
			//nfds = epoll_wait(epollfd, events, MAX_EVENTS, 1000);
			if (terminateTheProcess) {
		//		tpe.shutdownNow();

				tpe.shutdown();
				for (long i = 0;i < 4;++ i) {
					tpe.execute(write_to_a_file_descriptor, &in);
				}

				tpe.awaitTermination();

				// Clean up.
				{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "Clean up." << '\n';}

				break;
			}

			// ......

			//kill(getpid(), SIGINT);
			kill(getpid(), SIGTERM);
			//kill(getpid(), SIGQUIT);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> difference = end - start;
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "max threadNo = " << threadNo << '\n';}
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "time = " << difference.count() << " s\n";}
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "cnt = " << cnt << '\n';}
		{std::lock_guard<std::mutex> lock(stdCoutMutex_);std::cout << "CompletedTaskCount = " << tpe.getCompletedTaskCount() << '\n';}
	} while(0);

	return 0;
}


