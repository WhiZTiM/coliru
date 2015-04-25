//============================================================================
// Name        : AssyncAccessor.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <future>

template<class C>
class AssyncAccessor {
    public:

		AssyncAccessor(std::shared_ptr<C> o) : obj(o) {};

		template<class Fn, class ...Args>
		std::future<typename std::result_of<Fn(C,Args...)>::type> call(Fn&& f, Args&&... args) {
            typedef typename std::result_of<Fn(C,Args...)>::type RetType;

		    mut.lock();
		    // future from a packaged_task
    	    std::packaged_task<RetType()> task(std::bind(f, obj, args...)); 	// wrap the function
		    std::future<RetType> fut = task.get_future();  		// get a future
		    task_thr = std::thread(std::move(task));   		// launch on a thread
            task_thr.join();
			mut.unlock();
            return std::move(fut);
		}
        
    	template<class Fn, class ...Args>
		std::shared_future<typename std::result_of<Fn(C,Args...)>::type> async(Fn&& f, Args&&... args) {
            typedef typename std::result_of<Fn(C,Args...)>::type RetType;

		    mut.lock();
            if ( wait ) {
                wait();
                wait = nullptr;
            }
            
            // future from a packaged_task
		    std::shared_future<RetType> fut = std::async(std::launch::async, f, obj, args...);  		// get a future
            wait = std::bind( &std::shared_future<RetType>::wait, fut);
			mut.unlock();
            return fut;
		}        

        template<class Fn, class ...Args>
		typename std::result_of<Fn(C,Args...)>::type sync(Fn&& f, Args&&... args) {
            typedef typename std::result_of<Fn(C,Args...)>::type RetType;

		    mut.lock();

		    // future from a packaged_task
		    std::shared_future<RetType> fut = std::async(std::launch::async, f, obj, args...);  		// get a future
            wait = std::bind( &std::shared_future<RetType>::wait, fut);
			mut.unlock();
            return fut;
		}        



	private:
		std::shared_ptr<C>	    obj;
		std::thread			    task_thr;
		std::mutex			    mut;
    	std::function<void()>	wait;
        
};

class Foo {
    public:
	int bar(int i) { return i + 1; }
};

using namespace std;

int main() {
    Foo f;
    cout << " Sync: " << f.bar(0) << endl; // prints !!!Hello World!!!
    
    AssyncAccessor<Foo> aaFoo( std::make_shared<Foo>() );
    // cout << "Async: " << aaFoo.call(&Foo::bar, 8) << endl; // prints !!!Hello World!!!
    std::packaged_task<int()> task(std::bind(&Foo::bar, f, 1));
    std::future<int> result = task.get_future();
 
    task();
    
    cout << "Async: " << result.get() << endl; // prints !!!Hello World!!!

    cout << "Async: " << aaFoo.async(&Foo::bar, 2).get() << endl; // prints !!!Hello World!!!
    
	return 0;
}