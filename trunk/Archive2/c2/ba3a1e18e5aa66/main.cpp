#include <iostream>
#include <string>

using namespace std;

string cmdInput;

class aaccess {
    public:
    bool n = true;
    bool e = true;
    bool s = true;
    bool w = true;
    string ndesc = "You cant go that way.";
    string edesc = "You cant go that way.";
    string sdesc = "You cant go that way.";
    string wdesc = "You cant go that way.";
};

class area {
    public:
    string desc = "Default desc.";
    aaccess access;
};

int y = 3;
int x = 3;

area map[5][5];

void look() {
    cout << "Your coordinates are " << x << " , " << y << endl;
    cout << map[x][y].desc << endl;
}

int main() {
    do {
	    cin >> cmdInput;
	    if(cmdInput == "look") {
	        look();
	    }
	} while(cmdInput != "exit");
	return 0;
}