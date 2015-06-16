#include <thread>
#include <mutex> 
#include <iostream>

std::mutex shared_mutex;

enum message{
    hold_on = 0,
    release = 1
};

message inter_thread_message;

void thread_a_function(){
    while(true){
        message outer_message;
        
        shared_mutex.lock();
            outer_message = inter_thread_message;    // this is the critical part of the code.
        shared_mutex.unlock();
        
        switch(outer_message){
            case message::hold_on:
                std::cout << "hold on" << std::endl;
            break;
            
            case message::release:
                std::cout << "release" << std::endl;
            break;
        }
    }
}

int main()
{
    inter_thread_message = message::hold_on;
    
    std::thread thread_a(thread_a_function);
    while (true){                      /// thread A is looping too and will sync with the values below.
        shared_mutex.lock();
            switch(inter_thread_message){
                case message::hold_on:
                    inter_thread_message = message::release;
                break;
                
                case message::release:
                    inter_thread_message = message::hold_on;
                break;
            }
        shared_mutex.unlock();
    }
    
    thread_a.join();
}
