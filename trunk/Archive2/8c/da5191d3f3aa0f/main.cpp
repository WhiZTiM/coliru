#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

template <typename... Args>
void dump(Args const&... args) {
    static std::mutex stdout_mutex;
	stdout_mutex.lock(); (void)std::initializer_list<int> {((std::cerr << args),0)...}; stdout_mutex.unlock();
}

class priority_mutex : std::mutex
{
	std::priority_queue<std::size_t> queue;
	std::mutex qmutex;
	std::condition_variable cv;

public:

	using std::mutex::native_handle_type;
	using std::mutex::native_handle;
	using std::mutex::try_lock;

	void lock(std::size_t p) {
		dump("Locking ", p, '\n');
		if (!try_lock())
		{
			std::unique_lock<std::mutex> ulock(qmutex);
			queue.push(p);
			dump(p, " Pushed\n");

			cv.wait(ulock, [this, p] {return queue.top() == p && try_lock();});
			dump(p, " Locked\n");

			queue.pop();
			qmutex.unlock();
			cv.notify_all();
			dump(p, " Popped\n");
		}
	}

	void unlock() {
		std::mutex::unlock();
		cv.notify_all();
	}
};

int main()
{
	using namespace std::literals;

	priority_mutex m;
	m.lock(0);
	std::cerr << "Locked main\n";
	std::thread t([&]{m.lock(1); dump("t locked!\n"); m.unlock(); dump("t unlocked!\n");}),
	            u([&]{m.lock(3); dump("u locked!\n"); m.unlock(); dump("u unlocked!\n");}),
	            v([&]{m.lock(2); dump("v locked!\n"); m.unlock(); dump("v unlocked!\n");});
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	m.unlock();
	dump("Main unlocked!\n");

	t.join();
	u.join();
	v.join();
}
