#include <iostream>
#include <memory>



int main()
{
    std::cout << "start!\n";
    auto customArrayAllocator = [](unsigned int num){
        std::cout << "custom array allocator\n";
        return new int[num];
    };
    
    std::cout << "allocator constructed\n";
    
    auto customArrayDeleter = [](int *ptr){
        std::cout << "custom array deleter\n";
        delete[] ptr;
    };
    
    std::cout << "deleter constructed\n";
    
    std::unique_ptr<int[], decltype(customArrayDeleter)>
        myUnique(customArrayAllocator(4), customArrayDeleter);
        
    std::cout << "unique_ptr constructed\n";
    
    std::shared_ptr<int>
        myShared = std::move(myUnique);
        
    std::cout << "shared_ptr constructed\n";
}