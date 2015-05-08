#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <string.h>

#include <arpa/inet.h>

typedef struct berval {
    long    	bv_len;
	char		*bv_val;
} BerValue;


int main()
{
    std::string foo = "cq?yy 0a";
    
   // previous implentation
   const char* password = foo.c_str();
   char* pass_copy = new char[strlen(password)+1];
   strcpy(pass_copy, password);
   struct berval pass_struct;
   pass_struct.bv_val = pass_copy;
   pass_struct.bv_len = strlen(pass_copy);
   
   std::cout << pass_struct.bv_len << " " << pass_struct.bv_val << std::endl; // gives -> 8 cq?yy 0a
   
   // new implementation
   std::vector<char> pass_copy1 { password, password + strlen(password) + 1 };
   pass_struct.bv_val = pass_copy1.data();
   pass_struct.bv_len = pass_copy1.size();
   
   std::cout << pass_struct.bv_len << " " << pass_struct.bv_val << std::endl; // gives -> 9 cq?yy 0a
}
