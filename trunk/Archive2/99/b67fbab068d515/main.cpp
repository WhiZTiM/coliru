#include <string>
#include <iostream>

using namespace std;

int main(){

    string test = "username=kramsp&password=overfloww123"; 
    
    int username_start = test.find('=') + 1;    
    int username_end = test.find('&') - 1;
    int len = username_end - username_start + 1; 
    
    const char* username = test.substr(username_start, len).c_str();
    
    const char* password = test.substr(username_end + 11).c_str();

    cout << username << endl;
    cout << password << endl;
    
return 0;

}