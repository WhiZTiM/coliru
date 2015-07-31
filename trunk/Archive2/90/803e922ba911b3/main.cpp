#include <iostream>
#include <stdexcept>
using namespace std;

void foo(){
    cout << "foo executed" << endl;
}

void bar(){
    cout << "bar executed" << endl;
}

int main(){
    string choice;
    cin >> choice;
    
    if( choice == "foo")
        foo();
    else
        bar();
    return 0;
        
}