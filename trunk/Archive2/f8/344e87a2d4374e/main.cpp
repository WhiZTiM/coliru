#include <vector>    // for std::vector

struct bar {
    bar()=default;
    bar(bar const&)=delete;
    bar(bar&&)=default;
};

std::vector<bar> getVector()
{
    return {{}};
} 

int main()
{
}