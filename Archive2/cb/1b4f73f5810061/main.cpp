#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    using namespace std;
    std::istringstream read("2009-12-31 21:00:00, COUNTRY ,1.84296,350.947,60.72");

    string line;

    //I want to use this to hold the data temporarily
    string temp[5];

    while (std::getline(read, line))
    {
        int i=0;
        std::istringstream iss(line); // string stream
        while(std::getline(iss, temp[i], ','))
        {
            cout << i << ": " << temp[i] << endl;
            ++i;
        }
    }
}