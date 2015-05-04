#include <iostream>
#include <string>

//We're going to use <algorithm> to show how we can use
//std::transform to transform all of our characters to lowercase.
//Note: most likely not Unicode-safe
#include <algorithm>

//This program loops until it can find "walrus" in an input line.
int main() {
    std::string input;
    bool found_walrus = false;
    
    while (!found_walrus) {
        std::cout << "Hm, I didn't see \"Walrus\" in that last line...\n";
        std::cin >> input;
        
        //std::transform will transform each character in the string to lowercase for us.
        //That way, we can make sure that even if our input is ALL CAPS, we can still find walrus
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        //We use a member function of std::string to see if we can find walrus
        //If we can't find it, std::string.find() will return the defined constant
        //std::string::npos. So, let's check against that.
        if (input.find("walrus") != std::string::npos) {
            found_walrus = true;
        } 
        
        //Clear our input buffer string
        input.clear();
    }
    
    std::cout << "Ooh, I found walrus! Thanks!\n";
    return 0;
}