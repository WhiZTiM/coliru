#include <ostream>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
  std::string subjectString("subject");
  std::ostream tempStream(NULL);
  tempStream << subjectString;
  std::ostream& updatedStream = tempStream;
  std::stringstream ss;
  ss << updatedStream;
  std::cout << ss.str() << std::endl;
  return 0;
}