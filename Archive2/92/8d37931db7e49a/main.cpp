#include <iostream>
#include <stdio.h>
#include <string.h>
#include <regex>

using namespace std;


int main(int argc, char* argv[]) {

     string test = R"(<html><div><script>var link = "http://example.com/?key=dynamic_key";</script></div></html>)";

     //regex re("http://example.com/(*)");
     regex re("http://example\\.com/.*");
     smatch match;

     if (regex_search(test, match, re)) {

     cout<<"OK"<<endl;

     }

return 0;

}