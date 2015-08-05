#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int main()
{
    const char* path_info = "/v1/clients/client/";
    
    regex r( "/v1/clients/client" );
    cmatch m;
    
    cout << regex_match( path_info, m, r ) << endl;
    cout << m.size() << endl;
}
