#include <thread>
#include <mutex> 
#include <iostream>
#include <tbb/concurrent_queue.h>

std::mutex shared_mutex;

enum message{
    hold_on = 0,
    release = 1
};

int loop_count_a = 0;
int loop_count_b = 0;

tbb::concurrent_bounded_queue<message> messages;

void thread_a_function(){
    while(loop_count_b < 1500){
        message outer_message;
        messages.pop(outer_message);
        
        switch(outer_message){
            case message::hold_on:
                std::cout << "hold on" << std::endl;
            break;
            
            case message::release:
                std::cout << "release" << std::endl;
            break;
        }
        
        ++loop_count_b;
    }
}

int main()
{
    messages.set_capacity(1);
    auto inter_thread_message = message::hold_on;
    
    std::thread thread_a(thread_a_function);
    while (loop_count_a < 1500){
        switch(inter_thread_message){
            case message::hold_on:
                inter_thread_message = message::release;
            break;
            
            case message::release:
                inter_thread_message = message::hold_on;
            break;
        }
        
        messages.push(inter_thread_message);
        
        ++loop_count_a;
    }
    
    thread_a.join();
}
