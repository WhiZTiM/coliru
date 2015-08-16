#include<thread>
using namespace std;
void test (){
}

int main () {
    thread t1 (test);
    t1.join();
    return 0;
}