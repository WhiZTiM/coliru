#include <stdio.h>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct FullNameGen {
    FullNameGen() : seed(3), pkey(key) {};
    char operator()() {
        char returnChar = charTable[seed];

        seed += *pkey++;
        return returnChar;
    }
    int seed;
    const int* pkey;

    static const char charTable[];
    static const int key[];
};
const int FullNameGen::key[] = {2, -3, -2, 5, 1, -1, -2, 1, -3};
const char FullNameGen::charTable[] = {'k', 'g', 'b', 'l', 'e', 'o', ' '};

int main(int argc, char *arcv[]) {
    signed char c = -92;
    string fullName(10, '*');

    printf("Age: %d \n", c & (unsigned char) (~(1 << 7)));
  
    generate(fullName.begin(), fullName.end(), FullNameGen());
    cout << "FullName: " << fullName << endl;

    return EXIT_SUCCESS;
}