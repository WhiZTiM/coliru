#include <functional>
#include <iostream>
#include <tbb/concurrent_queue.h>
#include <thread>

enum class message {
    hold_on = 0,
    release = 1
};

void thread_function(tbb::concurrent_bounded_queue<message>& messages) {
    for (auto i = 0; i < 1500; ++i) {
        message outer_message;
        messages.pop(outer_message);

        switch(outer_message) {
        case message::hold_on:
            std::cout << "hold on" << std::endl;
            break;

        case message::release:
            std::cout << "release" << std::endl;
            break;
        }
    }
}

int main() {
    tbb::concurrent_bounded_queue<message> messages;

    std::thread thread(thread_function, std::ref(messages));

    auto to_send = message::hold_on;
    for (auto i = 0; i < 1500; ++i) {
        switch (to_send) {
        case message::hold_on:
            to_send = message::release;
            break;

        case message::release:
            to_send = message::hold_on;
            break;
        }
        
        messages.push(to_send);
    }
    
    thread.join();

    return 0;
}
