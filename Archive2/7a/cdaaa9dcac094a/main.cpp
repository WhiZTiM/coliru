#include <iostream>
#include <string>

using namespace std;

void write_vertically(int n){
string str = to_string(n);

if (str.length()> 1) {
cout<<stoi(str.substr(0,1))<<endl;
write_vertically(stoi(str.substr(1,str.length())));
     }

}

int main( ) {
write_vertically(1234567890);
return 0;
}