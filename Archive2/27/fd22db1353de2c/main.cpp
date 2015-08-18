#include <iostream>
#include <cstring>
#include <string>

int main()
{
   constexpr int max_size = 64;
   
   std::string test(max_size,0);                                // emulating your "test" variable
   
   const char* first_payload = "IP Address: 192.168.1.1";
   std::strcpy(&test[0],first_payload);                         // emulate gethostname() or other routine to copy some string data
   
   
   std::cout << "test capacity = " << test.capacity() << '\n';  // capacity should still be 64
   
   test.resize(std::strlen(test.c_str()));                      // Matt's suggestion
   
   
   test += "Hostname = Alejandro_PC";                           // copy over some more payload. 
   
   
   std::cout << "test capacity = " << test.capacity() << '\n';  // capacity _NOT_ increased!
   
   
   
   
}
