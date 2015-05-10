#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <unordered_map>

class SpinLock
{
public:
    SpinLock()
	{
		m_lock.clear(std::memory_order_release);
	}

	void lock()
	{
		for (int i = 0; m_lock.test_and_set(std::memory_order_acquire); ++i)
		{
			if (i > 64)
			{
				std::this_thread::yield();
			}
		}
	}

	void unlock()
	{
		m_lock.test_and_set(std::memory_order_release);
	}

private:
	std::atomic_flag m_lock;
};

class RWSpinLock
{
	const std::uint32_t WRITER = 0xF0000000;
	const std::uint32_t READERS = 0x7FFFFFFF;

public:
	RWSpinLock()
	{
		m_lock.store(0, std::memory_order_release);
	}

	void readLock()
	{
		std::uint32_t expected = m_lock.load(std::memory_order_acquire) & READERS;
		for (int i = 0; !m_lock.compare_exchange_weak(expected, expected + 1, std::memory_order_acquire); ++i)
		{
			expected &= READERS;
			yield(i);
		}
	}

	void readUnlock()
	{
		m_lock.fetch_sub(1, std::memory_order_release);
	}

	void writeLock()
	{
		std::uint32_t expected = m_lock.load(std::memory_order_acquire) & READERS;
		for (int i = 0; !m_lock.compare_exchange_weak(expected, expected | WRITER, std::memory_order_acquire); ++i)
		{
			expected &= READERS;
			yield(i);
		}

		for (int i = 0; m_lock.load(std::memory_order_acquire) != WRITER; ++i)
		{
			yield(i);
		}
	}

	void writeUnlock()
	{
		m_lock.store(0, std::memory_order_release);
	}

private:
	static void yield(int i)
	{
		if (i > 64)
		{
			std::this_thread::yield();
		}
	}

	std::atomic<std::uint32_t> m_lock;
};

RWSpinLock rw;
std::atomic<std::int32_t> w(0);
std::atomic<std::int32_t> r(0);
std::atomic<std::int32_t> c(0);
std::vector<int> rv;


std::unordered_map<int, int> m;

int read(int i)
{
	auto it = m.find(i);
	return it != m.end() ? it->second : 0;
}

void write(int i)
{
	auto result = m.insert(std::make_pair(i, 0));
	result.first->second += 1;
}

void reader(int n)
{
	for (int i = 0; i < n; i++)
	{
		rw.readLock();
		++r;
		read(i);
		if (w > 0)
		{
			++c;
		}
		rw.readUnlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void writer(int n)
{
	for (int i = 0; i < n; i++)
	{
		rw.writeLock();
		++w;
		write(i);
		if (r > 0)
		{
			rv.push_back(r);
			r = 0;
		}
		--w;
		rw.writeUnlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; i++)
	{
		threads.emplace_back(i % 4 ? reader : writer, 20);
	}

	for (auto& t : threads)
	{
		t.join();
	}

	printf("w=%d, c=%d \n", w.load(), c.load());

	for (auto v : rv)
	{
		printf("%d ", v);
	}
	printf("\n");

	for (auto& p : m)
	{
		printf("(%d, %d) ", p.first, p.second);
	}
	printf("\n");
	return 0;
}
