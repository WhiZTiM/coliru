//
//  可测试Boost.Lockfree的single-producer/single-consumer、
//  multiple-producer/multiple-consumer所耗费的时间，
//  使用C++11实现。
//



#define SPSC


#include <pthread.h>
#include <chrono>
#include <atomic>
#include <iostream>

#ifdef SPSC
#include <boost/lockfree/spsc_queue.hpp>
#else
#include <boost/lockfree/queue.hpp>
#endif

typedef void (*TaskFunction) (void *);
struct Task {
    TaskFunction taskFunction;
	void *arg;
};

#ifdef SPSC
const long iterations = 100000000; 
boost::lockfree::spsc_queue<Task> queue(1234);
#else
const long iterations = 1000000; 
boost::lockfree::queue<Task> queue(1234);
#endif

std::atomic<bool> created(false);
std::atomic<bool> done(false);

void TaskFunctionTest (void *arg) {
}

void * start_routine_producer (void *arg) {
	while (!created) 
		;

	long p;
	Task t;

	t.taskFunction = TaskFunctionTest;
	t.arg = &p;

	for (long i = 0; i < iterations; ++ i) {
		while (!queue.push(t))
			;
	}

	return 0;
}

void * start_routine_consumer (void *arg) {
	while (!created) 
		;

	Task t;
	while (!done) {
		while (queue.pop(t))
			;
	}

	while (queue.pop(t))
		;

	return 0;
}

int main( ) {
#ifdef SPSC
	#define PRODUCER_SIZE 1 
	#define CONSUMER_SIZE 1 
#else
	#define PRODUCER_SIZE 10
	#define CONSUMER_SIZE 10
#endif

	pthread_t thread_producer[PRODUCER_SIZE];
	pthread_t thread_consumer[CONSUMER_SIZE];

	void *ret;
	int p, c;

	p = 0;
	while (p < PRODUCER_SIZE) {
		pthread_create(&thread_producer[p], 0, start_routine_producer, 0);
		++ p;
	}
	c = 0;
	while (c < CONSUMER_SIZE) {
		pthread_create(&thread_consumer[c], 0, start_routine_consumer, 0);
		++ c;
	}

	auto start = std::chrono::high_resolution_clock::now();
	created = true;
	p = 0;
	while (p < PRODUCER_SIZE) {
		pthread_join(thread_producer[p], &ret);
		++ p;
	}
	done = true;
	c = 0;
	while (c < CONSUMER_SIZE) {
		pthread_join(thread_consumer[c], &ret);
		++ c;
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> difference = end - start;
	std::cout << "总时间：" << difference.count() << " s\n";
	std::cout << "单次时间：" << difference.count()/(iterations * (PRODUCER_SIZE + CONSUMER_SIZE)) << " s\n";
	std::cout << "push操作数量：" << iterations * PRODUCER_SIZE << std::endl;
	std::cout << "pop操作数量：" << iterations * CONSUMER_SIZE << std::endl;
	std::cout << "每秒执行的push、pop操作数量：" << (iterations * (PRODUCER_SIZE + CONSUMER_SIZE))/difference.count();

	return 0;
}


