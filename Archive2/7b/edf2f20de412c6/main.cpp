#include <iostream>
//#include <string> // Compiles with this, not without

int main()
{
   using namespace std;

   string first_name = "John";
   string last_name = "Doe";
   string full_name = first_name + " " + last_name;

   std::cout << "Hello, " << full_name << "!" << endl;

   cin.get();

   
   return 0;

}