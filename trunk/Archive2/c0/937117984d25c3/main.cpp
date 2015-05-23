#include <iostream>
#include <string>
using namespace std;

void stringCompare(string c, string d){
    if(c < d){
    cout << c << " is less than " << d <<endl;
    }
    else{
    cout << c << "is greater than" << d <<endl;
    }


}

int main(){
    
    stringCompare("A", "B");
    stringCompare("A", "b");
    stringCompare("c", "d");
}