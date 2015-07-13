#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string file = "temp";
    ofstream os;
    os.open(file + ".dat");
}