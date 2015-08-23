#include <iostream>
using namespace std;

void f(char){ 
    cout << "char\n";
}
 
void f(unsigned char){ 
    cout << "uchar\n";
} 

void f(signed char){ 
    cout << "schar\n";
}

int main() {

    char c = '0';
    unsigned char uc = c;
    signed char sc = c;

    f(c); 
    f(uc); 
    f(sc); 
}