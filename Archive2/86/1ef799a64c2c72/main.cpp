#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Foo
{
public:
    bool dump_dvars()
    {
        std::for_each(begin(seq), end(seq),
         [this](int) -> void
         {
             std::cout << output_file.is_open() << '\n';
         });
        
        return true;
    }
    
private:
    int seq[1];
    fstream output_file;
};

int main()
{
    Foo foo;
    foo.dump_dvars();
}