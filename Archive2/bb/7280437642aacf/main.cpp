#include <memory>
#include <mutex>

template <typename T>
class ThreadLock;

template <typename T>
class ThreadPtr {
private:
    friend class ThreadLock<T>;

	std::shared_ptr<T> m_object;
	std::shared_ptr<std::mutex> m_mutex;

public:
	template <typename... Args>
	ThreadPtr(Args&&... args)
		: m_object{std::make_shared<T>(std::forward<Args>(args)...)}
		, m_mutex{std::make_shared<std::mutex>()}
	{
	}

	ThreadPtr(std::shared_ptr<T> ptr)
		: m_object{std::move(ptr)}
		, m_mutex{std::make_shared<std::mutex>()}
	{
	}
};

template <typename T>
class ThreadLock {
private:
	ThreadPtr<T> &m_ptr;
	std::unique_lock<std::mutex> m_lock;

public:
	ThreadLock(ThreadPtr<T> &ptr)
		: m_ptr{ptr}
		, m_lock{*ptr.m_mutex}
	{
	}

	inline operator T &() noexcept
	{
		return *m_ptr.m_object;
	}

	inline operator const T &() const noexcept
	{
		return *m_ptr.m_object;
	}

	inline T *operator->() noexcept
	{
		return m_ptr.m_object.get();
	}

	inline const T operator->() const noexcept
	{
		return m_ptr.m_object.get();
	}
};

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

int main()
{
	ThreadPtr<int> ptr{1};

	thread t1([&] () {
		cout << "[thread 1], waiting\n";
		ThreadLock<int> object{ptr};
		cout << "[thread 1], Object acquired, waiting 3 seconds\n";
		this_thread::sleep_for(3s);
	});
	thread t2([&] () {
		cout << "[thread 2], waiting\n";
		ThreadLock<int> object{ptr};
		cout << "[thread 2], Object acquired, waiting 1 seconds\n";
		this_thread::sleep_for(1s);
	});

	t1.join();
	t2.join();

	return 0;
}