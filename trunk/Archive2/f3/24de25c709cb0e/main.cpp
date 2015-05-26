#include <string>

void uppercasify( std::string& ) {}

char title[] = "Effective C++, Item 19";

int main()
{
//uppercasify(             title  );    // error #1
  uppercasify( std::string(title) );    // error #2
}

//  uncomment/comment the two lines, and compile again