// Example program
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main()
{
ifstream f ("rez.txt");
if (f.is_open()){
    cout <<"V";
    }
    else cout <<"n";
}