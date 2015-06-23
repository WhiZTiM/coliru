#include <boost/thread.hpp>
#include <boost/make_shared.hpp>

using namespace boost;

int ltuae(int factor) {
    this_thread::sleep_for(chrono::milliseconds(rand()%1000));
    return factor*42;
}

int main() {
    std::vector<unique_future<int> > futures;
    std::vector<shared_ptr<thread> > threads;
    for (int i=0; i<10; ++i)
    {
        packaged_task<int> pt([=] { 
                sleep(rand()%1000); 
                return i*42; 
            });
        futures.emplace_back(pt.get_future());
        threads.emplace_back(make_shared<thread>(std::move(pt)));
    }

    for (auto& f : futures)
        std::cout << "Return: " << f.get() << "\n";

    for (auto& t: threads)
        if (t->joinable())
            t->join();
}
