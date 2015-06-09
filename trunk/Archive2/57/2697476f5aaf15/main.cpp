#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <unistd.h>

using namespace std;

void test2(timed_mutex* _t_mutex)
{
    cout << "Try to have the lock\n";
	bool got_lock = _t_mutex->try_lock_for(std::chrono::seconds(10));
	if (got_lock)
    {
        cout << "I have the lock !\n";
		_t_mutex->unlock();
    }
    else
    {
        cout << "I don't have the lock !\n";
    }
}

void test1(timed_mutex* _t_mutex)
{
	_t_mutex->lock();
	cout << "Sleep 4 secs\n";
	for (int i = 0; i < 4; i++)
	{
		sleep(1);
		cout << i+1 << endl;
	}
	_t_mutex->unlock();
}

int main()
{
	timed_mutex t_mutex;
	thread t1 = thread(test1, &t_mutex);
	thread t2 = thread(test2, &t_mutex);
	t2.join();
	t1.join();

    cout << "It works with g++-4.9 (c++11) but not with g++-4.8 (c++11)";
	return 0;
}