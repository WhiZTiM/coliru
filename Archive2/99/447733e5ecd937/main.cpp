#include <iostream>
#include <cassert>
#include <functional>

// Until now:

struct CurrentSafeInt
{
    CurrentSafeInt(int i) : i(i) {}
    int i = 0;
    operator int() { return i; }
};

typedef CurrentSafeInt CurrentResourceAmount;
typedef CurrentSafeInt CurrentMonsterId;


// Probably it can be done in other ways, but I think this one is very nice:

template <typename T>
struct SafeInt
{
    SafeInt(int i) : i(i) {}
    int i = 0;
    operator int() { return i; }
};

struct ResourceAmount_tag {};
typedef SafeInt<ResourceAmount_tag> ResourceAmount;

struct MonsterId_tag {};
typedef SafeInt<MonsterId_tag> MonsterId;


int main()
{
    CurrentResourceAmount cra = {1};
    CurrentMonsterId cmi = cra; // We don't want this to be allowed.
    std::cout << cmi << std::endl;
    
    ResourceAmount ra = {2};
    //MonsterId mi = ra;
    MonsterId mi = (int)ra;
    std::cout << mi << std::endl;
}