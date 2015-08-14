#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

typedef std::function<void(const string& hello)> Func;

void Shareify(Func func) {
    std::shared_ptr<Func> shared_func(&func);
    
    shared_func->operator()("hello");
}

int main() {
    Shareify(
        [](const string& hello) {
            cout << hello << endl;
        });
        
            
}










































