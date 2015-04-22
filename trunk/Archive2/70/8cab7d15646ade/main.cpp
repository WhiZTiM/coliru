#include <iostream>
#include <string>

using namespace std;

auto foo() {
    string *acc = new string[2];
    string some_string;

    for ( int i = 0; i < 2; i ++ ) {

     if ( i == 0 )
        some_string = "ab";
     else 
        some_string = "cd";
     acc[i] = some_string;
     some_string = "";
    }
    return acc;
}

int main() {
    auto arr = foo();
    std::cout << arr[0] << arr[1];
    delete[] arr;
}