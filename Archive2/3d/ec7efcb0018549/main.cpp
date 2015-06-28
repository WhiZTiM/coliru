    #include <iostream>
    #include <memory>
    #include <thread>
    #include <mutex>
    
    static std::mutex cout_mutex;
    
    struct CoutGuard : public std::unique_lock<std::mutex> {
        CoutGuard() : unique_lock(cout_mutex) {}
    };
    
    struct doSomething {
        void fn() {
            CoutGuard guard;
            std::cout << std::this_thread::get_id() << " running doSomething "
                << (void*)this << "\n";
        }
    };

    thread_local std::unique_ptr<doSomething> tls_dsptr; // DoSomethingPoinTeR

    void testFn() {
        doSomething* dsp = tls_dsptr.get();
        if (dsp == nullptr) {
            tls_dsptr = std::make_unique<doSomething>();
            dsp = tls_dsptr.get();
            CoutGuard guard;
            std::cout << std::this_thread::get_id() << " allocated "
                << (void*)dsp << "\n";
        } else {
            CoutGuard guard;
            std::cout << std::this_thread::get_id() << " re-use\n";
        }
        dsp->fn();
        std::this_thread::yield();
    }

    void thread_fn() {
        testFn();
        testFn();
        testFn();
    }
    
    int main() {
        std::thread t1(thread_fn);
        std::thread t2(thread_fn);
        t2.join();
        t1.join();
    }
    