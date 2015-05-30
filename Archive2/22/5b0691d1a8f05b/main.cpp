#include <map>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

bool isComment(string line){
    string comment = "/";
    if(line.find(comment) != string::npos){
        return true;
    }else{
        return false;
    }
}

bool isMemLoc(string line){
    string symbol = "@";
    if(line.find(symbol) != string::npos){
        cout << "CONSTANT YO" << endl;
        //ConvertToBinary(atoi(line.c_str));
        return true;
    }else{
        return false;
    }

}

int main() {
    std::string s = "1\n2\n3\n13\n@12\n@12\n@13\n2\n";
    std::istringstream infile{s};
    std::string tempLine;
    
    while (getline(infile, tempLine)){
        if(isComment(tempLine))
            continue;
        if(isMemLoc(tempLine)){
            tempLine.erase(0,1);
            cout << tempLine << endl;
            continue;
        }
    
        //print to terminal and pass to file
        cout << tempLine << endl;   
    }
}