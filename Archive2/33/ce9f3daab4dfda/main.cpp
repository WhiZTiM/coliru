#include <iostream>
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>

#define PRINT(X) std::cout << X << std::endl;

using std::thread;

static unsigned dtor_count = 0;
static unsigned ctor_count = 0;
static unsigned mtor_count = 0;

class scoped_thread {
    thread t;
public:
	explicit scoped_thread(thread t_) :
		t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("No thread!");
		PRINT("Called scoped_thread CTor");
		ctor_count++;
	}
	~scoped_thread()
	{
		if (t.joinable())
			t.join();
		PRINT("Called scope_thread DTor");
		dtor_count++;
	}
	scoped_thread(const scoped_thread&) = delete; // copy CTor
	scoped_thread& operator=(const scoped_thread&) = delete; // copy init
	scoped_thread(scoped_thread&& s) {
		t = std::move(s.t);
		mtor_count++;
	};
};

void do_work(int i) { PRINT("Made Thread : " << i); };
void thread_vector_example()
{
	// normal version: have to call thread join
    /*
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 10; ++i)
		threads.push_back(std::thread(do_work, i));
	std::for_each(begin(threads), end(threads),
		std::mem_fn(&std::thread::join));	
	*/
	
	std::vector<scoped_thread> sthreads;
	for (unsigned i = 0; i < 10; ++i) {
		PRINT(":::" << i+1);
		sthreads.emplace_back(std::thread(do_work, i));
	}
	
}	
	

int main() {
	// your code goes here
    
    thread_vector_example();
    PRINT("Number of CTors used: " << ctor_count);
	PRINT("Number of move CTors used: " << mtor_count);
	PRINT("Number of DTors used: " << dtor_count);
    
	return 0;
}