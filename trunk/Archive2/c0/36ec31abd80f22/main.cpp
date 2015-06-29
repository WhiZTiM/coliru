#include <iostream>
#include <functional>
#include <memory>
#include <sstream>

int main(int argc, char* argv[])
{
    std::stringstream ss;
    ss << "test";
    ss.read(nullptr, 0);
    
    printf("ok\n");
}