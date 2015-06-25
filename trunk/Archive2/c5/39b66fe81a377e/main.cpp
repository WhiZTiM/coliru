#include <iostream>
#include <atomic>
using namespace std;    
typedef enum day{sun =0, mon, tue}day;    

int main() {
    atomic<day> a(sun);
    cout<<a<<endl;
    return 0;
}