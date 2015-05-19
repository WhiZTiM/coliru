#include <iostream>
using namespace std;

int main(int argc, const char* argv[]){
    argc = 5;
    argv = new const char*[5]{
        argv[0], //argv[0] ist immer der name der executable
        "hey",
        "blub",
        "42",
        "37"
    };
    for(int i = 0; i < argc; i++){
		cout << "Argument " << i << ": " << argv[i] << endl;
	}
}

