#include <cstdio>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::ifstream infile("thefile.txt");
    int a, b;
    while (infile >> a >> b)
    {
        printf("%s, %s", a, b);
    }   
}