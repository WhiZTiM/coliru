#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <mutex>
#include <memory>
#include <utility>
#include <iostream>

class ThreadRAII {
public:
    enum class DtorAction {join, detach};

    explicit ThreadRAII(DtorAction a = DtorAction::join) : action(a) {}
    ThreadRAII(boost::thread&& t, DtorAction a = DtorAction::join) : action(a), t(std::move(t)) {}
    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default;

    void interrupt_and_join() {
        std::lock_guard<std::mutex> lk{*mtx};
        if (t.joinable()) {
            t.interrupt();
            if (action == DtorAction::join) {
                t.join();
            } else {
                t.detach();
            }
        }
    }

    ~ThreadRAII() {
        interrupt_and_join();
    }

    boost::thread& get() { return t; }

private:
    std::unique_ptr<std::mutex> mtx = std::make_unique<std::mutex>();
    DtorAction action;
    boost::thread t;
};

struct MyObj {
    void start() { // simplified example
        boost::packaged_task<void> task{[]() {
                std::cout << "Hello\n";
                boost::this_thread::sleep_for(boost::chrono::milliseconds{2000});
                std::cout << "World\n";
            }
        };
        thr = ThreadRAII{boost::thread{std::move(task)}}; 
    }
    
    void stop() { // in real apoosp, might run concurrently with the thr destructor
        thr.interrupt_and_join();
    }

    ThreadRAII thr;
};

int main() {
    MyObj obj;
    obj.start();
}
