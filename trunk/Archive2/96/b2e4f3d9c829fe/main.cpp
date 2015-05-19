#include <iostream>
#include <string>
#include <vector>




#define orig_memset memset
#define memset checked_memset

template <class T>
void* checked_memset(T* ptr, int value, size_t num) {
  static_assert(std::is_pod<T>::value, "memset on non-POD");
  return orig_memset(ptr, value, num);
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{


    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
