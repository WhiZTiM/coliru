#include <vector>
#include <iterator>
#include <fstream>

int main()
{
    std::ifstream stream;
    std::vector<char> buf(std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>());
    return 0;
}