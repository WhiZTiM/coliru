#include <array>
#include <atomic>
#include <thread>
#include <iostream>

// DISRUPTOR


__attribute__((aligned(128))) std::array<int, 1024> buffer;
__attribute__((aligned(128))) std::atomic<int> write_offset_{0};
__attribute__((aligned(128))) std::atomic<int> cursor_{0};


void publish(int event)
{
    auto old_offset = write_offset_.fetch_add(1);
    buffer[old_offset] = event;
    cursor_ = old_offset + 1;
}



void consume(std::ostream& os, const char* id, int old_cursor)
{
    
    int new_cursor = cursor_;
    
    for (;;)
    {
        while (old_cursor == new_cursor)
        {
            new_cursor = cursor_;
        }
        for (auto i = buffer.data() + old_cursor; i != buffer.data() + new_cursor; ++i)
        {
            os << id << '-' << *i << ' ';
            if (*i == -1)
            {
                os << "===" << std::endl;
                return;
            }
        }
        os << std::endl;
        sched_yield();
        old_cursor = new_cursor;
    }
}


int main()
{
    std::thread([]{ std::this_thread::sleep_for(std::chrono::seconds(1)); abort(); }).detach();
    
    std::thread c1([] { consume(std::cout, "c1", cursor_); });
    std::thread c2([] { consume(std::cerr, "c2", cursor_); });
    
    std::thread producer([]
    {
        for (int i = 0; i != 1000; ++i)
        {
            publish(i);
            if (i % 4 == 0) sched_yield();
        }
        publish(-1);
    });
    
    
    c1.join();
    c2.join();
    producer.join();
}
