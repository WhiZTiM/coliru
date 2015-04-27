#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cstdlib>

using namespace std;


void openFiles(std::ofstream& myfile, std::string& result, const std::string& name, const std::string& ending)
{
    std::string str;
    for(int i=1;i != 101;++i) {
        if(i%20==0) {
            ostringstream temp;            // use a string stream to convert int...
            temp << i;
            str = temp.str();              // ...to str
            result = name + str + ending;  // concatenating strings.
            myfile.open(result);
            myfile << "The value is:" << i;
            myfile.close();
        }
    }
}

int main ()
{
    std::string name = "John"; //int age = 21;
    std::string result;
    std::string ending = ".txt";
    std::ofstream myfile;
    openFiles(myfile, result, name, ending);
}
