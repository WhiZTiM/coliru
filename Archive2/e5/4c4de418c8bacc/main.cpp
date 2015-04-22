#include <cwchar>
#include <cassert>

int main()
{
    const wchar_t* wstr = L"Hello world";
    const size_t size_of_wide_cstr_in_bytes = wcslen(wstr) * sizeof(wchar_t);
    
    assert(sizeof(wchar_t) == 4);             // on this particular system
    assert(size_of_wide_cstr_in_bytes == 44); // on this particular system
}
