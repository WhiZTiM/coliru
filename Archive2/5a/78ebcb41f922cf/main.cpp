#include <iostream>


int main() {
    int  x = 0;
    
    for(int i=0; i<=100; i++) {
        int y = 7;
    
        if (i=1) continue;
        else if (x !=0) {
            std::cout << "*****ERROR*****" << std::endl;
            break;
        }
    
    }
}
