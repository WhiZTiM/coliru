#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <unistd.h>

using namespace std;

void test2(timed_mutex* _t_mutex)
{
    sleep(0.01);
    cout << "thread 2 : Try to get the lock\n";
	bool got_lock = _t_mutex->try_lock_for(std::chrono::nanoseconds(5000000000));
	if (got_lock)
    {
        cout << "thread 2 : I get the lock !\n";
		_t_mutex->unlock();
    }
    else
    {
        cout << "thread 2 : I don't get the lock !\n";
    }
}

void test1(timed_mutex* _t_mutex)
{
	_t_mutex->lock();
	cout << "thread 1 : Sleep 3 secs\n";
	for (int i = 0; i < 3; i++)
	{
		sleep(1);
		cout << "thread 1 : " <<  i+1 << endl;
	}
	_t_mutex->unlock();
}

int main()
{
	timed_mutex t_mutex;
	thread t1 = thread(test1, &t_mutex);
	thread t2 = thread(test2, &t_mutex);
	t1.join();
	t2.join();

    cout << "It works with g++-4.9 (c++11) but not with g++-4.8 (c++11)";
	return 0;
}