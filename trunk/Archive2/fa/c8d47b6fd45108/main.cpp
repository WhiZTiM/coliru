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
    auto shared_func = std::make_shared<Func>(func);
    
    (*shared_func)("hello");
}

int main() {
    Shareify(
        [](const string& hello) {
            cout << hello << endl;
        });
        
            
}










































