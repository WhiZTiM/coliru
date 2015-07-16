#include <iostream>

#include <assert.h>

#ifdef DEBUG
#pragma message "Debug enabled"
#else
#pragma message "Debug disabled"
#endif

#ifdef RELEASE
#pragma message "Release enabled"
#else
#pragma message "Release disabled"
#endif

#ifdef _DEBUG
#pragma message "_DEBUG enabled"
#else
#pragma message "_DEBUG disabled"
#endif

#ifdef ENABLE_ASSERTS
#pragma message "ENABLE_ASSERTS enabled"
#else
#pragma message "ENABLE_ASSERTS disabled"
#endif

#ifdef NDEBUG
#pragma message "NDEBUG enabled"
#else
#pragma message "NDEBUG disabled"
#endif

int main()
{
    assert(false);
    std::cout << "Hello World" << std::endl;
}