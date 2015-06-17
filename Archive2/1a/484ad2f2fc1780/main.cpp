//Title of this code
//Rextester.Program.Main is the entry point for your code. Don't change it.
//Compiler version 4.0.30319.17929 for Microsoft (R) .NET Framework 4.5

#include <iostream>


using namespace std;


class A
{
    public:
        A() { 
            cout << "Hello" << endl;
        }
        
        ~A(){
            cout << "Good bye" << endl;
        }
};


int main()
{
    {
        A a;
    }
    
    cout << "Still in main" << endl;
}