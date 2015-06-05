#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <unistd.h>

using namespace std;

void test2(timed_mutex* m)
{
    cout << "Try to have the lock\n";
	bool got_lock = m->try_lock_for(std::chrono::seconds(15));
	if(got_lock)
    {
        cout << "I have the lock !\n";
    	m->unlock();
    }
    else
    {
        cout << "I don't have the lock !\n";
    }
}

void test1(timed_mutex* m)
{
	m->lock();
	cout << "Sleep 10 secs\n";
	for (int i = 0; i < 10; i++)
	{
		sleep(1);
		cout << i+1 << endl;
	}
	m->unlock();
}

int main()
{
	timed_mutex m;
	thread t1 = thread(test1, &m);
	thread t2 = thread(test2, &m);
	t2.join();
	t1.join();

    cout << "It works with gcc 4.9 (c++11) but not with gcc 4.8 (c++11)";
	return 0;
}