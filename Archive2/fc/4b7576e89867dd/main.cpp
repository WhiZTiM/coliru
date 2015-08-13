#include <iostream>
#include <string>

int main()
{
  std::string message;
  getline(std::cin, message);                       // Read from input stream.
  std::cout.write(message.c_str(), message.size()); // Write to output stream.
}