#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void threadMethod(){
}

void do_join(std::thread& t)
{
    std::thread::id  tid =  t.get_id(); 
    t.join();
    cout << tid <<  " joined." << endl;
    
}

void join_all(std::vector<std::thread>& v)
{
    std::for_each(v.begin(),v.end(),do_join);
}

int main()
{         
    std::vector<std::thread> myThreads;

    for(int i = 1; i <= 3; i++)
    {

        myThreads.push_back(std::thread(threadMethod));

    }


    join_all(ref(myThreads));
}