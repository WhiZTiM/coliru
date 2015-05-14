#include <string>

const std::string& get()
{
    using namespace std::literals;
    return ""s;
}

int main()
{
    get();
}
