#include <unordered_set>

int main()
{
    std::unordered_set<void*> voidStarUnorderedSet;
    void* const myConstVoidStar = NULL; // marche
    //const void* myConstVoidStar = NULL; // ne marche pas
    
    voidStarUnorderedSet.insert(myConstVoidStar);
    
    return 0;
}