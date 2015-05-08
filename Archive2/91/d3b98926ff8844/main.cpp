#include <iomanip>
#include <sstream>

int main()
{
    std::ostringstream os; 
    os << "0x" << std::setfill('0') << std::hex;
}
