#include <iostream>
#include <string>
#include <sstream> // location of stringstream definition

void doDifferentThingsFromString(const std::string &str){
    std::string
        command;
    std::istringstream
        stream{str}; // construct an input string stream
        
    stream >> command;
    if(command == "line"){
        std::cout << stream.str() << '\n';
    }
    else{
        std::cout << "not line!\n";
    }
}

int main(){
    
    doDifferentThingsFromString("line Alice and \nBob were having an adventure.");
    doDifferentThingsFromString("well this won't print anything at all");
    
}