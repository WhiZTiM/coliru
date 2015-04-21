#include <iostream>
#include <array>
#include <cstdint>

using namespace std;

typedef uint32_t ClientId;

std::array<char, 32> buffer;

void send(ClientId clientId, const char payload[], std::size_t payloadSize)
{
    cout << "Non-templated send.\n";
}

template <typename Func>
void send(ClientId clientId, Func convFunc, std::size_t payloadSize)
{
    convFunc();
    
    cout << "Templated send.\n";
    
    send(clientId, const_cast<const char*>(buffer.data()), payloadSize);
}

int main()
{
    int val = 42;
    auto convFunc = []() {};
    
    send(1, convFunc, 16);
}
