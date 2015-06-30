#include <iostream> 
#include <thread> 
#include <mutex> 
#include <condition_variable> 
using namespace std;

/* Question:

*/

class ProducerConsumer {
private:
    int value; // 1 
	bool produced; // 2 
	mutex m;
	condition_variable cv;

public:
	ProducerConsumer() : value(-1), produced(false) {}

	void producer(unsigned int count) {
		for (int i = count; i >= 0; --i) {
			{
                unique_lock<mutex> l(m);
			    cv.wait(l, [this](){ return !produced; }); // 1 
			}
            
			cout << "Producer sets value to " << i << endl;

			value = i;
			produced = true;
			cv.notify_one(); // 2 
		}
	}

	void consumer(unsigned int thread_id) {
		do {
            {
			    unique_lock<mutex> l(m);
			    cv.wait(l, [this](){ return produced; });
            }
            
			cout << "Consumer thread " << thread_id << "...now is in control: " << value << endl;
			produced = false;
			cv.notify_one();
		} while (value);
	}
};

int main() {
	// your code goes here 

	ProducerConsumer p;
	thread t1(&ProducerConsumer::consumer, &p, 1);
	thread t2(&ProducerConsumer::consumer, &p, 2);
	thread t3(&ProducerConsumer::producer, &p, 3);

	t1.join();
	t2.join();
	t3.join();

    cout << "end" << endl;
    
	return 0;
}