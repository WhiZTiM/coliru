// C++ 11
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main(){

    regex e("username=([[:w:]]+)&password=([[:w:]]+)");
    
    string test = "username=kramsp&password=overfloww123";
    
    smatch m;
    regex_search(test, m, e);
    
    if (m.size() > 2)
    {
        const char *username = m[1].str().c_str();
        const char *password = m[2].str().c_str();
     
        cout << username << endl;
        cout << password << endl;
    }

return 0;

}