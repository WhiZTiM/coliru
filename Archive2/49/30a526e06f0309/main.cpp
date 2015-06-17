#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
 
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i
std::vector<std::thread> g_threads;
void safe_increment()
{
    //std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
 
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
 
    // g_i_mutex is automatically released when lock
    // goes out of scope

}
 
int main()
{
    std::cout << __func__ << ": " << g_i << '\n';
 
 for(std::size_t index = 0; index < 200; index++)
 {
    std::thread tt(safe_increment);
    g_threads.push_back(tt);
 }
 for(auto& thread : g_threads)
 {
     thread.join();
 }

    std::cout << __func__ << ": " << g_i << '\n';
}