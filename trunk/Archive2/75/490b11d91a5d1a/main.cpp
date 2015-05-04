#include <iostream>
#include <string>

//This program is extremely crude, but it indeed works for its intended purpose.
//There are many other better ways to do this.
int main() {
    
    //Here, we use a std::string to hold our input.
    //We will then turn this into a float once we have read in a "full number".
    std::string token;
    char c;
    
    //Here's how we store our measurements.
    float degrees = 0;
    float minutes = 0;
    float seconds = 0;
    
    std::cout << "Please input a degrees, minutes, seconds measurement as (D,M,S): ";
    
    //While we read in characters
    while(std::cin.get(c)) {
        //If it is part of a number, it is part of our "token"
        if (c >= '0' && c <= '9' || c == '.') {
            token += c;
        //If we have ended reading a number, let's "cast" to a float
        //then, reset the token std::string
        } else if (c == ',' || c == ')') {
            //All of these if statements translate to:
            //If X is 0 (since 0 == false in C++)
            if (!degrees)
                //We can use the C++11 function called "std::stof",
                //which will turn read our string until it finds a single
                //float number and then return that float to us.
                degrees = std::stof(token);
            else if (!minutes)
                minutes = std::stof(token);
            else if (!seconds)
                seconds = std::stof(token);
            
            //We can use a MEMBER function of a std::string object
            //to clear the std::string for us so that it is empty once again.
            token.clear();
        }
        
        //As always, we want to halt if we see a ')', which marks the end
        //of our input
        if (c == ')')
            break;
    }
    //This prints out a newline character
    std::cout << "\n";
    
    //Print out our final variables
    std::cout << "Degrees: " << degrees << '\n';
    std::cout << "Minutes: " << minutes << '\n';
    std::cout << "Seconds: " << seconds << '\n';
    
    return 0;
}