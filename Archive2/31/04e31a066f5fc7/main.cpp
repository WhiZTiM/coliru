#include <tuple>

struct pair {
    int& first;
    int& second;
};

int main()
{
    {
        int i = 42;
        int& ref = std::get<0>(std::tie(i, i));
        return ref;
    }
    
    {
        int i = 33;
        int& ref = pair { i, i }.first;
        return ref;
    }
}
