#include <algorithm>
#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


using Clock = std::chrono::high_resolution_clock;


volatile long no_optimize;


void sum(std::vector<int>& vec)
{
    long result = 0;
    for (auto& el : vec)
    {
        result += el; 
    }
    no_optimize = result;
}


void test_read(std::vector<int>& vec, bool silent = false)
{
    auto start_time = Clock::now();    
    sum(vec);
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    if (!silent) std::cout << elapsed << std::endl;
}


void test_write(std::vector<int>& s, bool silent = false)
{
    auto start_time = Clock::now();    
    std::random_shuffle(s.begin(), s.end());
    no_optimize = s[0];
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    if (!silent) std::cout << elapsed << std::endl;
}

auto big = [] {
    std::vector<int> vec;
    while (vec.size() != 100 * 1024)
    {
        vec.push_back(vec.size());
    }
    return vec;
}();

auto small = []
{
    std::vector<int> vec;
    while (vec.size() != 1024)
    {
        vec.push_back(vec.size());
    }
    return vec;
}();




void readers()
{
        

    std::thread t1([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t2([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t3([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t4([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    auto start_time = Clock::now();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    std::cout << "4 readers + 0 writers: " << elapsed << std::endl;
}

void four_writer()
{
    
        

    std::thread t1([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t2([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t3([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t4([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    auto start_time = Clock::now();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    std::cout << "0 readers + 4 writers: " << elapsed << std::endl;
}


void three_writer()
{
    
        

    std::thread t1([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t2([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t3([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t4([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    auto start_time = Clock::now();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    std::cout << "1 readers + 3 writers: " << elapsed << std::endl;
}



void two_writer()
{
    
        

    std::thread t1([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t2([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t3([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    std::thread t4([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    auto start_time = Clock::now();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    std::cout << "2 readers + 2 writers: " << elapsed << std::endl;
}


void one_writer()
{
    std::thread t1([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t2([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t3([=]() mutable { for (int i = 0; i != 20; ++i) { test_read(big, true); } });
    std::thread t4([=]() mutable { for (int i = 0; i != 20; ++i) { test_write(big, true); } });
    auto start_time = Clock::now();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
    std::cout << "3 readers + 1 writers: " << elapsed << std::endl;
}

int main()
{
    readers();
    one_writer();
    two_writer();
    three_writer();
    four_writer();

}
