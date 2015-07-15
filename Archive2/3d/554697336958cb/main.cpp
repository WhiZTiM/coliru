#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
    for(int i = 1; i < argc; ++i){
        cout << argv[i] << endl;
        reverse(argv[i], argv[i] + strlen(argv[i]));
        cout << argv[i] << endl;
    }
    return 0;
}
