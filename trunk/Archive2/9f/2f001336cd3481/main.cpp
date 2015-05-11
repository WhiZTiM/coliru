#include <vector>
#include <vector>
#include <iostream>
#include <cstddef>

using namespace std;

int main() {
    auto N = 10;
    auto free_list_size = N * sizeof(uintptr_t);
    void * mem = malloc(N * sizeof(char) + free_list_size);
    char *start = (char*)(mem) + free_list_size;
    
    // populate start to end
    auto tmp = start;
    for (int i = 0; i < 10; ++i) {
        *tmp = 'a';
        std::cout << (void*)tmp << ": " << *tmp << std::endl;
        tmp += 1;
    }
    
    std::cout << "---" << std::endl;
    
    auto free_list = (uintptr_t**)(mem);
    for (int i = 0; i < 10; ++i) {
        *free_list++ = (uintptr_t*)((char*)start + i);
    }

   free_list = (uintptr_t**)(mem);
    for (int i = 0; i < 10; ++i) {
        std::cout << free_list << ": " << *free_list << ": " << (char)**free_list << std::endl;
        free_list += 1;
    }
}