#include <iostream>
#include <vector>
#include <string>

// head file
class JsonResponse
{
public:
    template<typename T>
    void add(const std::string &, const T &);
};

template<typename T>
void JsonResponse::add(const std::string & name, const T & t)
{
    // do something
}

int main() {}