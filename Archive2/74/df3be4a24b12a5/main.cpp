//Title of this code
//Rextester.Program.Main is the entry point for your code. Don't change it.
//Compiler version 4.0.30319.17929 for Microsoft (R) .NET Framework 4.5

#include <iostream>


using namespace std;


class A
{
    public:
        A(std::string name)
        : m_name(name)
        { 
            cout << "Hello" << endl;
        }
        
        ~A(){
            cout << "Good bye" << endl;
        }
        
        const std::string& Name() const
        {
            return m_name;
        }
        
    private:
        std::string m_name;
};


int main()
{
    {
        A a { "Jagan" };
        
        std::cout << a.Name() << endl;
    }
    
    cout << "Still in main" << endl;
}