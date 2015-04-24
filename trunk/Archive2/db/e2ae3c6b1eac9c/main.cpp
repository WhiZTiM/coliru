#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    // note that cin does not appear to be working...
    string str = "CAT";
    regex substr("[aeiouy]", regex_constants::icase); // ignore case
    
	if (regex_match(str, substr)) {
		cout << "String matched\n";
	} 
	else {
		cout << "String did NOT match\n";
	}
	
}