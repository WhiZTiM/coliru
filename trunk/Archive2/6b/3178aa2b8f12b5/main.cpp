#include<iostream>
#include<thread>
#include<mutex>

void myf(std::mutex& )
{
    std::cout << "hi\n";
}


int main(int , char** ) 
{
    std::mutex mtx;

    std::thread t(myf, std::ref(mtx));

    t.join(); 
    return 0; 
}