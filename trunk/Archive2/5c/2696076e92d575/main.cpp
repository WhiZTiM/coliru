#include <algorithm>
#include <iostream>
#include <vector>


int main()
{
    std::vector<bool> myvector(8, false);
    // Just for testing
    for(std::vector<bool>::iterator it = myvector.begin();
        it != myvector.end(); it++){
        std::cout << ((*it)? "True" : "False") << std::endl; // Prints False 8 times, never prints true
    }
    
    if(std::find(myvector.begin(), myvector.end(), true) == myvector.end()){
        std::cout << "ENTERED\n";
    }
}