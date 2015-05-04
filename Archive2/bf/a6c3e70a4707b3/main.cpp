#include <iostream>
#include <string>

int main(int argc, char** argv) {
    
    std::string argument;
    //std::strings are initialized as empty strings
    
    if (argv[1]) {
        argument += argv[1];
        //This is short hand for adding the contents of argv[1]
        //to the argument string.
    }
    /* 
    If we don't check for argv[1] first, we may get a
    nasty error that will just freeze the program.
    */
       
    std::cout << argument << '\n';
    return 0;
}