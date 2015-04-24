#include <vector>
#include <iterator>
#include <fstream>

int main()
{
    std::ifstream stream;
    std::vector<char> buf(std::istreambuf_iterator<char>(stream),
        (std::istreambuf_iterator<char>()));
    if (buf.size())
        return 1;
    return 0;
}