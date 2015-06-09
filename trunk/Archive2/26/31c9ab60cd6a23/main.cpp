#include <sstream>
#include <iostream>
#include <iomanip>

int main()
{
    int results = 0;
    
    for (unsigned long i = 0; i <= 999999999999999; ++i)
    {
        std::ostringstream oss;
        oss << "0." << std::setfill('0') << std::setw(15) << i;
        std::istringstream iss(oss.str());
        double d;
        iss >> d;
        std::ostringstream oss2;
        oss2 << std::fixed << std::setprecision(15) << d;
        if (oss.str() != oss2.str())
        {
            std::cout << "from " << oss.str() << '\n' << "  to " << oss2.str() << '\n';
            if (++results > 50) exit(0);
        }
    }
}